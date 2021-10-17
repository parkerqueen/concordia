#ifndef SPHERE_H_
#define SPHERE_H_

#include <memory>

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include "Material.h"

using std::shared_ptr;

class Sphere : public Hittable {
  public:
    Point3 center;
    double radius;
    shared_ptr<Material> material;

    Sphere() {}
    Sphere(const Point3& cen, const double rad, shared_ptr<Material> mat)
        : center(cen), radius(rad), material(mat) {}

    bool hit(const Ray& ray, const double t_min, const double t_max,
             HitRecord& hit_record) const override {
        const Vector3 oc = ray.origin - center;

        const double a = ray.direction.squared_norm();
        const double half_b = dot(ray.direction, oc);
        const double c = oc.squared_norm() - (radius * radius);

        const double discriminant = half_b * half_b - a * c;
        if (discriminant < 0.0) return false;
        const double sqrt_discriminant = sqrt(discriminant);

        double root = (-half_b - sqrt_discriminant) / a;
        if (root < t_min || root > t_max) {
            root = (-half_b + sqrt(discriminant)) / a;
            if (root < t_min || root > t_max) return false;
        }

        hit_record.ray_t = root;
        hit_record.point = ray.at(root);
        hit_record.hit_material = material;
        hit_record.set_face_normal(ray, (hit_record.point - center) / radius);
        return true;
    }
};

#endif