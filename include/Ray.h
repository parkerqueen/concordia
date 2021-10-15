#ifndef RAY_H_
#define RAY_H_

#include "Vector3.h"

class Ray {
  public:
    Point3 origin;
    Vector3 direction;

    constexpr Ray() {}
    constexpr Ray(const Point3& orig, const Vector3& dir) : origin(orig), direction(dir) {}

    constexpr Point3 at(const double t) const { return origin + t * direction; }
};

#endif