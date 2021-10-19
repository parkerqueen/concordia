#include "utility.h"

Color3 ray_color(const Ray& ray, const Hittable& world, const uint depth) {
    if (depth == 0) return Color3{0.0, 0.0, 0.0};

    HitRecord hrec;
    if (world.hit(ray, 0.001, INF, hrec)) {
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

int main() {
    HittableList world;
    Camera camera(CAM_LOOKFROM, CAM_LOOKAT, CAM_VUP, ASPECT_RATIO, CAM_VERTICAL_FIELD_OF_VIEW,
                  CAM_APERTURE, CAM_FOCUS_DISTANCE);

    const auto ground_material = make_shared<Lambertian>(Color3{0.8, 0.8, 0.0});
    const auto sphere_left_material = make_shared<Dielectric>(1.5);
    const auto sphere_right_material = make_shared<Metal>(Color3{0.8, 0.6, 0.2}, 1.0);
    const auto sphere_center_material = make_shared<Lambertian>(Color3{0.1, 0.2, 0.5});

    world.add(make_shared<Sphere>(Point3{0.0, -100.5, -1}, 100.0, ground_material));
    world.add(make_shared<Sphere>(Point3{-1.0, 0.0, -1.0}, 0.5, sphere_left_material));
    world.add(make_shared<Sphere>(Point3{-1.0, 0.0, -1.0}, -0.45, sphere_left_material));
    world.add(make_shared<Sphere>(Point3{1.0, 0.0, -1.0}, 0.5, sphere_right_material));
    world.add(make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5, sphere_center_material));

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