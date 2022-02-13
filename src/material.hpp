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

class dielectric: public material {

private:
    double ir; // index of refraction

public:
    dielectric(double _ir): ir(_ir) {}

    virtual bool scatter (
        const ray& r_in, const hit_record& rec, color& attenuation, ray& ray_out
    ) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face? 1.0 / ir: ir;
        vec3 unit_direction = normalize(r_in.get_direction());

        double cos_theta = fmin(-unit_direction * rec.normal, 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool reflect_flg = refraction_ratio * sin_theta > 1.0;
        vec3 dir;

        if (reflect_flg || reflectance(cos_theta, refraction_ratio) > random_double()) {
            dir = reflect(unit_direction, rec.normal);
        }
        else {
            dir = refract(unit_direction, rec.normal, refraction_ratio);
        }

        ray_out = ray(rec.p, dir);
        return true;
    }  

private:
    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};