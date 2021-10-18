#ifndef CAMERA_H_
#define CAMERA_H_

#include <cmath>

#include "Vector3.h"
#include "Ray.h"
#include "utility.h"

class Camera {
  public:
    Point3 origin;
    Point3 lower_left;
    Vector3 vertical;
    Vector3 horizontal;
    Vector3 u, v, w;
    double lens_radius;

    constexpr Camera(const Point3& lookfrom, const Point3& lookat, const Vector3& vup,
                     const double aspect_ratio, const double vfov, const double aperture,
                     const double focus_distance) {
        const double viewport_height = 2.0 * tan(degs_to_rads(vfov) / 2);
        const double viewport_width = aspect_ratio * viewport_height;

        w = (lookfrom - lookat).unit_vector();
        u = cross(vup, w).unit_vector();
        v = cross(w, u).unit_vector();

        origin = lookfrom;
        lens_radius = aperture / 2.0;

        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left = origin - horizontal / 2 - vertical / 2 - focus_distance * w;
    }

    Ray get_ray(const double s, const double t) {
        const Vector3 rd = lens_radius * Vector3::random_in_unit_disk();
        const Vector3 offset = u * rd.x + v * rd.y;
        return Ray{origin + offset, lower_left + s * horizontal + t * vertical - origin - offset};
    }
};

#endif