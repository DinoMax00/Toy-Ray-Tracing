#pragma once

/// Common Constants and Utility Functions

#include <cmath>
#include <limits>
#include <memory>

// usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;


// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = cos(-1);


// utility functions
inline double degree_to_radians(double degrees) {
    return degrees * pi / 180;
}


// common headers
#include "ray.hpp"
#include "mathlib.hpp"