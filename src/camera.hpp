#pragma once

#include "rtweekend.h"

class camera {

private:
    point origin;
    point lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double len_radius;

public:
    camera(
        point lookfrom,
        point lookat,
        vec3 vup,
        double fov, 
        double aspect_ratio,
        double aperture, // 光圈
        double focus_dist
    ) {
        double theta = degree_to_radians(fov);
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;
        
        w = normalize(lookfrom - lookat);
        u = normalize(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - (horizontal + vertical) / 2 - focus_dist * w;

        len_radius = aperture / 2;
    }

    ray get_ray(double s, double t) const {
        vec3 rd = len_radius * random_in_unit_disk();
        vec3 offset = u * rd.x + v * rd.y;

        return ray(
            origin + offset, 
            lower_left_corner + s * horizontal + t * vertical - origin - offset
        );
    }
};