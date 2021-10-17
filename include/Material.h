#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"

class Material {
  public:
    virtual constexpr bool scatter(const Ray& ray, const HitRecord& hit_record, Color3& attenuation,
                                   Ray& scattered) const = 0;
    virtual ~Material() = default;
};

class Lambertian : public Material {
  public:
    Color3 albedo;

    constexpr Lambertian(const Color3& alb) : albedo(alb) {}
    constexpr bool scatter(const Ray&, const HitRecord& hit_record, Color3& attenuation,
                           Ray& scattered) const override {
        Vector3 scatter_dir = hit_record.normal + Vector3::random_unit_vector();
        if (scatter_dir.near_zero()) scatter_dir = hit_record.normal;

        attenuation = albedo;
        scattered = Ray{hit_record.point, scatter_dir};

        return true;
    }
};

class Metal : public Material {
  public:
    Color3 albedo;

    constexpr Metal(const Color3& alb) : albedo(alb) {}
    constexpr bool scatter(const Ray& ray, const HitRecord& hit_record, Color3& attenuation,
                           Ray& scattered) const override {
        const Vector3 scatter_dir = ray.direction.unit_vector().reflect(hit_record.normal);

        attenuation = albedo;
        scattered = Ray{hit_record.point, scatter_dir};

        return dot(scattered.direction, hit_record.normal) > 0;
    }
};

#endif