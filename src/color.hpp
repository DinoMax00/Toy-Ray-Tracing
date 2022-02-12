#pragma once

#include <iostream>

#include "rtweekend.h"

void put_pixel(color cl, int samples_per_pixel) {
    auto r = cl.x;
    auto g = cl.y;
    auto b = cl.z;

    // divide the color by the number of samples and gamma-correct for gamma=2.0
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // rgb value in range [0, 1]
    std::cout << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}