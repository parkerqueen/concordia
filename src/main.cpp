#include "utility.h"

Color3 ray_color(const Ray& ray, const Hittable& world) {
    HitRecord hrec;
    if (world.hit(ray, 0, INF, hrec)) { return 0.5 * (hrec.normal + Color3{1.0, 1.0, 1.0}); }

    const auto unit_direction = ray.direction.unit_vector();
    const auto t = 0.5 * (unit_direction.y + 1.0);

    return (1.0 - t) * Color3{1.0, 1.0, 1.0} + t * Color3{0.5, 0.7, 1.0};
}

int main() {
    const double aspect_ratio = 16.0 / 9.0;

    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * aspect_ratio;

    const double focal_length = 1.0;
    const auto origin = Vector3{0.0, 0.0, 0.0};
    const auto horizontal = Vector3{viewport_width, 0.0, 0.0};
    const auto vertical = Vector3{0.0, viewport_height, 0.0};
    const auto lower_left_corner =
        origin - horizontal / 2.0 - vertical / 2.0 - Vector3{0.0, 0.0, focal_length};

    HittableList world;
    world.add(make_shared<Sphere>(Point3{0.0, 0.0, -1.0}, 0.5));
    world.add(make_shared<Sphere>(Point3{0.0, -100.5, -1}, 100));

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height; j >= 0; j--) {
        std::cerr << "SCANLINES REMAINING: " << j << "\n" << std::flush;

        for (int i = 0; i < image_width; i++) {
            const auto u = static_cast<double>(i) / (image_width - 1);
            const auto v = static_cast<double>(j) / (image_height - 1);
            const auto r = Ray{origin, lower_left_corner + u * horizontal + v * vertical};
            const auto pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    return EXIT_SUCCESS;
}