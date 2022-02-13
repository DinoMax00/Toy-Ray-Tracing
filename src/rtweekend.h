#pragma once

/// Common Constants and Utility Functions

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

/// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;


/// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = acos(-1);


/// utility functions
inline double degree_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    // return a random real in [0, 1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // return a random real in [min, max)
    return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
    x = std::min(x, max);
    x = std::max(x, min);
    return x;
}

// common headers
#include "ray.hpp"
#include "mathlib.hpp"