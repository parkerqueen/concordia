#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <cmath>

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include "utility.h"

class Material {
  public:
    virtual bool scatter(const Ray& ray, const HitRecord& hit_record, Color3& attenuation,
                         Ray& scattered) const = 0;
    virtual ~Material() = default;
};

class Lambertian : public Material {
  public:
    Color3 albedo;

    constexpr Lambertian(const Color3& alb) : albedo(alb) {}
    bool scatter(const Ray&, const HitRecord& hit_record, Color3& attenuation,
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
    double fuzz;
    Color3 albedo;

    constexpr Metal(const Color3& alb, const double fuz) : fuzz(fuz), albedo(alb) {}
    bool scatter(const Ray& ray, const HitRecord& hit_record, Color3& attenuation,
                 Ray& scattered) const override {
        const Vector3 scatter_dir = ray.direction.unit_vector().reflect(hit_record.normal);

        attenuation = albedo;
        scattered = Ray{hit_record.point, fuzz * scatter_dir};

        return dot(scattered.direction, hit_record.normal) > 0;
    }
};

class Dielectric : public Material {
  public:
    double refraction_index;

    constexpr Dielectric(const double ri) : refraction_index(ri) {}
    bool scatter(const Ray& ray, const HitRecord& hit_record, Color3& attenuation,
                 Ray& scattered) const override {
        const double ri = hit_record.front_face ? (1.0 / refraction_index) : refraction_index;

        const Vector3 ray_unit_dir = ray.direction.unit_vector();
        const double cos_theta = fmin(dot(-ray_unit_dir, hit_record.normal), 1.0);
        const double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        Vector3 scattered_dir;
        if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double())
            scattered_dir = ray_unit_dir.reflect(hit_record.normal);
        else
            scattered_dir = ray_unit_dir.refract(hit_record.normal, ri);

        attenuation = Color3{1.0, 1.0, 1.0};
        scattered = Ray{hit_record.point, scattered_dir};

        return true;
    }

  private:
    static constexpr double reflectance(const double cosine, const double ri) {
        const double r0 = pow((1.0 - ri) / (1.0 + ri), 2);
        return r0 + (1.0 - r0) * pow(1 - cosine, 5);
    }
};

#endif