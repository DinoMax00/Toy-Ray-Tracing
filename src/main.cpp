#include <iostream>

#include "rtweekend.h"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

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

    /// World
    hittable_list world;
    world.add(make_shared<sphere>(point(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point(0, -100.5, -1), 100));

    /// Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    // distance between eye and screen
    auto foacl_length = 1.0;

    auto ori = vec3(0, 0, 0);
    // x-axis and y-axis
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto start_point = -(horizontal + vertical) / 2 - vec3(0, 0, foacl_length);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        // std::cerr << "Drawing row: " << j << std::endl;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
        
            ray r(ori, start_point + u * horizontal + v * vertical - ori);
            color cl = ray_color(r, world);
            put_pixel(cl);
        }
    }
}