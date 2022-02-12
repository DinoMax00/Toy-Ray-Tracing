#include <iostream>

#include "rtweekend.h"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"


// check intersection
double hit_sphere(point center, double radius, const ray& r) {
    vec3 temp = r.get_origin() - center;
    double a = r.get_direction() * r.get_direction();
    double b = 2 * r.get_direction() * temp;
    double c = temp * temp - radius * radius;
    double delta = b * b - 4 * a * c;
    if (delta < 0) 
        return -1;
    else {
        return (-b - sqrt(delta)) / (2 * a); 
    }
}

color ray_color(ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unit_direction = normalize(r.get_direction());
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    /// Image
    constexpr double aspect_ratio = 16.0 / 9;
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 100;

    /// World
    hittable_list world;
    world.add(make_shared<sphere>(point(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point(0, -100.5, -1), 100));

    /// Camera
    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        // std::cerr << "Drawing row: " << j << std::endl;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            put_pixel(pixel_color, samples_per_pixel);
        }
    }
}