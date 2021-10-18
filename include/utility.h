#ifndef UTILITY_H_
#define UTILITY_H_

#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include <random>

using std::make_shared;
using std::shared_ptr;
using uint = unsigned int;

constexpr double PI = 3.1415926535897932385;
constexpr double INF = std::numeric_limits<double>::infinity();

constexpr double degs_to_rads(const double degrees) { return degrees * PI / 180.0; }

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(const double min, const double max) {
    return min + (max - min) * random_double();
}

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Material.h"
#include "Camera.h"
#include "PPMWriter.h"

#endif