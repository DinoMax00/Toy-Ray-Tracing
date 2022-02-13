#include <iostream>

#include "rtweekend.h"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;
    
    if (depth <= 0)
        return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray ray_out;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, ray_out)) {
            return inner_mult(attenuation, ray_color(ray_out, world, depth - 1));
        }
        return color(0, 0, 0);
    }

    vec3 unit_direction = normalize(r.get_direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    /// Image
    constexpr double aspect_ratio = 16.0 / 9.0;
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 100;
    constexpr int max_depth = 50;

    /// World
    hittable_list world;
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point( 1.0,    0.0, -1.0),   0.5, material_right));

    /// camera
    camera cam(point(-2,2,1), point(0,0,-1), vec3(0,1,0), 20, aspect_ratio);

    /// Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        if (j % 32 == 0) std::cerr << "Drawing row: " << j << std::endl;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            put_pixel(pixel_color, samples_per_pixel);
        }
    }

    return 0;
}