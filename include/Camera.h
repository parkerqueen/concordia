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

    constexpr Camera(const Point3& lookfrom, const Point3& lookat, const Vector3& vup,
                     const double aspect_ratio, const double vfov) {
        const double viewport_height = 2.0 * tan(degs_to_rads(vfov) / 2);
        const double viewport_width = aspect_ratio * viewport_height;

        const Vector3 w = (lookfrom - lookat).unit_vector();
        const Vector3 u = cross(vup, w).unit_vector();
        const Vector3 v = cross(w, u).unit_vector();

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left = origin - horizontal / 2 - vertical / 2 - w;
    }

    constexpr Ray get_ray(const double s, const double t) {
        return Ray{origin, lower_left + s * horizontal + t * vertical - origin};
    }
};

#endif