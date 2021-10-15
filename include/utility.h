#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"

using std::make_shared;
using std::shared_ptr;
using uint = unsigned int;

constexpr double PI = 3.1415926535897932385;
constexpr double INF = std::numeric_limits<double>::infinity();

constexpr double degs_to_rads(const double degrees) { return degrees * PI / 180.0; }

inline std::ostream& write_color(std::ostream& out, const Color3& color) {
    return out << static_cast<int>(255.999 * color.x) << ' ' << static_cast<int>(255.999 * color.y)
               << ' ' << static_cast<int>(255.999 * color.z) << '\n';
}

#endif