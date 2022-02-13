#pragma once

#include "rtweekend.h"

class camera {

private:
    point origin;
    point lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

public:
    camera(
        point lookfrom,
        point lookat,
        vec3 vup,
        double fov, 
        double aspect_ratio
    ) {
        double theta = degree_to_radians(fov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;
        
        auto w = normalize(lookfrom - lookat);
        auto u = normalize(cross(vup, w));
        auto v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - (horizontal + vertical) / 2 - w;
    }

    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
};