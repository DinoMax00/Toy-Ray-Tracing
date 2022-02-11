#pragma once

#include <iostream>

#include "mathlib.hpp"

void put_pixel(color cl) {
    // rgb value in range [0, 1]
    std::cout << static_cast<int>(255.999 * cl.x) << ' '
        << static_cast<int>(255.999 * cl.y) << ' '
        << static_cast<int>(255.999 * cl.z) << '\n';
}