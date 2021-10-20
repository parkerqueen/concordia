#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "utility.h"

constexpr const double ASPECT_RATIO = 16.0 / 9.0;

constexpr const int IMAGE_WIDTH = 1200;
constexpr const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

constexpr const int RAYS_PER_PIXEL = 500;
constexpr const int MAX_SHADOW_RAYS_PER_RAY = 50;

constexpr const double CAM_APERTURE = 0.05;
constexpr const double CAM_FOCUS_DISTANCE = 10.0;
constexpr const double CAM_VERTICAL_FIELD_OF_VIEW = 20.0;

constexpr const Vector3 CAM_VUP{0.0, 1.0, 0.0};
constexpr const Point3 CAM_LOOKAT{0.0, 0.0, 0.0};
constexpr const Point3 CAM_LOOKFROM{13.0, 2.0, 3.0};

constexpr const double INTERSECTION_T_MIN = 0.001;
constexpr const double INTERSECTION_T_MAX = INF;

constexpr const int PPM_COLOR_SCALING = 256;

#endif