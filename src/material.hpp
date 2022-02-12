#pragma once

#include <cmath>
#include "rtweekend.h"
// #include "hittable.h"

class hit_record;

class material {

public:
    virtual bool scatter (
        // 第三个参数是衰减系数
        const ray& r_in, const hit_record& rec, color& attenuation, ray& ray_out
    ) const = 0;

};


class lambertian: public material {

private:
    color albedo;
    
public:
    lambertian(const color& a): albedo(a) {}

    virtual bool scatter (
        const ray& r_in, const hit_record& rec, color& attenuation, ray& ray_out
    ) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        ray_out = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal: public material {

private:
    color albedo;
    double fuzz;

public:
    metal(const color& a, double f): albedo(a), fuzz(std::min(f, 1.0)) {}

    virtual bool scatter (
        const ray& r_in, const hit_record& rec, color& attenuation, ray& ray_out
    ) const override {
        vec3 reflected = reflect(normalize(r_in.get_direction()), rec.normal);
        ray_out = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return ray_out.get_direction() * rec.normal > 0;
    }
};
