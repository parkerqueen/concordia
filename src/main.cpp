#include "utility.h"

Color3 ray_color(const Ray& ray, const Hittable& world, const uint depth) {
    if (depth == 0) return Color3{0.0, 0.0, 0.0};

    HitRecord hrec;
    if (world.hit(ray, INTERSECTION_T_MIN, INTERSECTION_T_MAX, hrec)) {
        Ray scattered;
        Color3 attenuation;

        if (hrec.hit_material->scatter(ray, hrec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);

        return Color3{0.0, 0.0, 0.0};
    }

    const auto unit_direction = ray.direction.unit_vector();
    const auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * Color3{1.0, 1.0, 1.0} + t * Color3{0.5, 0.7, 1.0};
}

HittableList random_scene() {
    HittableList world;
    const double sphere_radius = 0.2, glass_ri = 1.5;

    for (int x = -5; x <= 5; x++) {
        for (int y = -5; y <= 5; y++) {
            const double choose_material = random_double();
            const Point3 sphere_center{x + random_double(), sphere_radius, y + random_double()};

            if (choose_material < 0.8) {
                const auto albedo = Color3::random() * Color3::random();
                const auto material = make_shared<Lambertian>(albedo);
                world.add(make_shared<Sphere>(sphere_center, sphere_radius, material));
            } else if (choose_material < 0.95) {
                const auto fuzz = random_double(0.0, 0.5);
                const auto albedo = Color3::random();
                const auto material = make_shared<Metal>(albedo, fuzz);
                world.add(make_shared<Sphere>(sphere_center, sphere_radius, material));
            } else {
                const auto material = make_shared<Dielectric>(glass_ri);
                world.add(make_shared<Sphere>(sphere_center, sphere_radius, material));
            }
        }
    }

    const auto ground_material = make_shared<Lambertian>(Color3{0.5, 0.5, 0.5});
    world.add(make_shared<Sphere>(Point3{0.0, -1000.0, 0.0}, 1000.0, ground_material));

    const auto material1 = make_shared<Lambertian>(Color3{0.4, 0.2, 0.1});
    world.add(make_shared<Sphere>(Point3{-4.0, 1.0, 0.0}, 1.0, material1));

    const auto material2 = make_shared<Metal>(Color3{0.7, 0.6, 0.5}, 0.2);
    world.add(make_shared<Sphere>(Point3{4.0, 1.0, 0.0}, 1.0, material2));

    const auto material3 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3{0.0, 1.0, 0.0}, 1.0, material3));

    return world;
}

int main() {
    HittableList world = random_scene();
    Camera camera(CAM_LOOKFROM, CAM_LOOKAT, CAM_VUP, ASPECT_RATIO, CAM_VERTICAL_FIELD_OF_VIEW,
                  CAM_APERTURE, CAM_FOCUS_DISTANCE);

    PPMWriter ppm_writer("output.ppm", IMAGE_WIDTH, IMAGE_HEIGHT);
    for (int j = IMAGE_HEIGHT; j >= 0; j--) {
        std::cout << "SCANLINES REMAINING: " << j << "\n";

        for (int i = 0; i < IMAGE_WIDTH; i++) {
            Color3 pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < RAYS_PER_PIXEL; s++) {
                const auto u = static_cast<double>(i + random_double()) / (IMAGE_WIDTH - 1);
                const auto v = static_cast<double>(j + random_double()) / (IMAGE_HEIGHT - 1);
                const auto r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, MAX_SHADOW_RAYS_PER_RAY);
            }

            ppm_writer.write_color(pixel_color, RAYS_PER_PIXEL);
        }
    }

    return EXIT_SUCCESS;
}