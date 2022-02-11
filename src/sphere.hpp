#pragma once

#include "hittable.hpp"
#include "mathlib.hpp"


class sphere: public hittable {

private:
    point center;
    double radius;

public:
    sphere() {}
    sphere(point c, double r): center(c), radius(r) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    assert(t_min < t_max);
    vec3 temp = r.get_origin() - center;
    double a = r.get_direction() * r.get_direction();
    double b = 2 * r.get_direction() * temp;
    double c = temp * temp - radius * radius;
    double delta = b * b - 4 * a * c;
    if (delta < 0) 
        return false;
    
    // find the nearest root that lies in the acceptable range.
    double root = (-b - sqrt(delta)) / (2 * a); 
    if (root < t_min || root > t_max) {
        root = (-b + sqrt(delta)) / (2 * a); 
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.get_point(root);
    rec.normal = (rec.p - center) / radius;
}