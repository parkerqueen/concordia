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
    const double aperture = 0.05;
    const double aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const int max_depth = 50;
    const int samples_per_pixel = 100;

    const Point3 lookfrom(0.0, 0.0, 1.0);
    const Point3 lookat(0.0, 0.0, -1.0);
    const double focus_distance = (lookfrom - lookat).norm();

    HittableList world;
    Camera camera(lookfrom, lookat, Vector3{0.0, 1.0, 0.0}, aspect_ratio, 90.0, aperture,
                  focus_distance);

    const auto ground_material = make_shared<Lambertian>(Color3{0.8, 0.8, 0.0});
    const auto sphere_left_material = make_shared<Dielectric>(1.5);
    const auto sphere_right_material = make_shared<Metal>(Color3{0.8, 0.6, 0.2}, 1.0);
    const auto sphere_center_material = make_shared<Lambertian>(Color3{0.1, 0.2, 0.5});

    world.add(make_shared<Sphere>(Point3{0.0, -100.5, -1}, 100.0, ground_material));
    world.add(make_shared<Sphere>(Point3{-1.0, 0.0, -1.0}, 0.5, sphere_left_material));
    world.add(make_shared<Sphere>(Point3{-1.0, 0.0, -1.0}, -0.45, sphere_left_material));
    world.add(make_shared<Sphere>(Point3{1.0, 0.0, -1.0}, 0.5, sphere_right_material));
    world.add(make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5, sphere_center_material));

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height; j >= 0; j--) {
        std::cerr << "SCANLINES REMAINING: " << j << "\n" << std::flush;

        for (int i = 0; i < image_width; i++) {
            Color3 pixel_color(0.0, 0.0, 0.0);
            for (int s = 0; s < samples_per_pixel; s++) {
                const auto u = static_cast<double>(i + random_double()) / (image_width - 1);
                const auto v = static_cast<double>(j + random_double()) / (image_height - 1);
                const auto r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    return EXIT_SUCCESS;
}