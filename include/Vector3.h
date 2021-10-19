#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

#include "utility.h"

class Vector3;
constexpr Vector3 operator+(const Vector3&, const Vector3&);
constexpr Vector3 operator-(const Vector3&, const Vector3&);
constexpr Vector3 operator/(const Vector3&, const double);
constexpr Vector3 operator*(const double s, const Vector3&);
constexpr double dot(const Vector3&, const Vector3&);

class Vector3 {
  public:
    double x, y, z;

  public:
    constexpr Vector3() : x(0), y(0), z(0){};
    constexpr Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}

    constexpr Vector3 operator-() const { return Vector3{-x, -y, -z}; }

    constexpr Vector3& operator+=(const Vector3& u) {
        x += u.x;
        y += u.y;
        z += u.z;
        return *this;
    }

    constexpr Vector3& operator-=(const Vector3& u) {
        x -= u.x;
        y -= u.y;
        z -= u.z;
        return *this;
    }

    constexpr double squared_norm() const { return x * x + y * y + z * z; }

    double norm() const { return sqrt(squared_norm()); }

    constexpr Vector3 unit_vector() const { return *this / norm(); }

    constexpr Vector3 reflect(const Vector3& normal) const {
        const auto& self = *this;
        return self - 2 * dot(self, normal) * normal;
    }

    constexpr Vector3 refract(const Vector3& normal, const double refraction_index) const {
        const auto& self = *this;
        const double cos_theta = fmin(dot(-self, normal), 1.0);
        const Vector3 r_out_perp = refraction_index * (self + cos_theta * normal);
        const Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.squared_norm())) * normal;

        return r_out_perp + r_out_parallel;
    }

    constexpr bool near_zero(const double thresh = 1e-8) const {
        return fabs(x) < thresh && fabs(y) < thresh && fabs(z) < thresh;
    }

    static Vector3 random(const double min = 0.0, const double max = 1.0) {
        return Vector3{random_double(min, max), random_double(min, max), random_double(min, max)};
    }

    static Vector3 random_in_unit_sphere() {
        while (true) {
            const auto vector = random(-1.0, 1.0);
            if (vector.squared_norm() >= 1.0) continue;
            return vector;
        }
    }

    static Vector3 random_in_unit_disk() {
        while (true) {
            const auto vector = Vector3{random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0};
            if (vector.squared_norm() >= 1.0) continue;
            return vector;
        }
    }

    static Vector3 random_unit_vector() { return random_in_unit_sphere().unit_vector(); }
};

constexpr Vector3 operator+(const Vector3& u, const Vector3& v) {
    return Vector3{u.x + v.x, u.y + v.y, u.z + v.z};
}

constexpr Vector3 operator-(const Vector3& u, const Vector3& v) { return u + (-v); }

constexpr Vector3 operator*(const Vector3& u, const Vector3& v) {
    return Vector3{u.x * v.x, u.y * v.y, u.z * v.z};
}

constexpr Vector3 operator*(const Vector3& u, const double s) {
    return Vector3{u.x * s, u.y * s, u.z * s};
}

constexpr Vector3 operator*(const double s, const Vector3& u) { return u * s; }

constexpr Vector3 operator/(const Vector3& u, const double s) { return u * (1.0 / s); }

constexpr double dot(const Vector3& u, const Vector3& v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

constexpr Vector3 cross(const Vector3& u, const Vector3& v) {
    return Vector3{u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x};
}

using Point3 = Vector3;
using Color3 = Vector3;

#endif