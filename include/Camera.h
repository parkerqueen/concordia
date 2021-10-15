#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector3.h"

class Camera {
  public:
    Point3 origin;
    Point3 lower_left;
    Vector3 vertical;
    Vector3 horizontal;

    constexpr Camera() {
        const double aspect_ratio = 16.0 / 9.0;
        const double viewport_height = 2.0;
        const double viewport_width = aspect_ratio * viewport_height;
        const double focal_length = 1.0;

        origin = Point3{0.0, 0.0, 0.0};
        vertical = Vector3{0.0, viewport_height, 0.0};
        horizontal = Vector3{viewport_width, 0.0, 0.0};
        lower_left = origin - horizontal / 2 - vertical / 2 - Vector3{0.0, 0.0, focal_length};
    }

    constexpr Ray get_ray(const double u, const double v) {
        return Ray{origin, lower_left + u * horizontal + v * vertical - origin};
    }
};

#endif