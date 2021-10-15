#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

class Vector3;
constexpr Vector3 operator/(const Vector3&, const double);

class Vector3 {
  public:
    double x, y, z;

  public:
    constexpr Vector3() : x(0), y(0), z(0){};
    constexpr Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}

    constexpr Vector3 operator-() const { return Vector3{-x, -y, -z}; }
    constexpr double squared_norm() const { return x * x + y * y + z * z; }
    double norm() const { return sqrt(squared_norm()); }
    constexpr Vector3 unit_vector() const { return *this / norm(); }
};

constexpr Vector3 operator+(const Vector3& u, const Vector3& v) {
    return Vector3{u.x + v.x, u.y + v.y, u.z + v.z};
}

constexpr Vector3 operator-(const Vector3& u, const Vector3& v) { return u + (-v); }

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