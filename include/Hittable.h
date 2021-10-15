#ifndef HITTABLE_H_
#define HITTABLE_H_

#include "Vector3.h"
#include "Ray.h"

struct HitRecord {
  public:
    Point3 point;
    Vector3 normal;
    double ray_t;
    bool front_face;

    constexpr void set_face_normal(const Ray& ray, const Vector3& outwards_normal) {
        front_face = dot(ray.direction, outwards_normal) < 0;
        normal = front_face ? outwards_normal : -outwards_normal;
    }
};

class Hittable {
  public:
    virtual constexpr bool hit(const Ray& ray, const double t_min, const double t_max,
                               HitRecord& hit_record) const = 0;
    virtual ~Hittable() = default;
};

#endif