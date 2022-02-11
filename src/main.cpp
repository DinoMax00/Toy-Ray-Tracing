#include <iostream>

#include "mathlib.hpp"
#include "color.hpp"
#include "ray.hpp"

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

color ray_color(ray& r) {
    double t = hit_sphere(point(0, 0, -1), 0.5, r);
    if (t > 0) {
        vec3 n = normalize(r.get_point(t) - vec3(0, 0, -1));
        return 0.5 * color(n.x + 1, n.y + 1, n.z + 1);
    }

    vec3 unit_direction = normalize(r.get_direction());
    t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    /// Image
    constexpr double aspect_ratio = 16.0 / 9;
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

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
            color cl = ray_color(r);
            put_pixel(cl);
        }
    }
}