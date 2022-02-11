#pragma

#include "ray.hpp"

/// An Abstraction for hittable objects

class hit_record {

public:
    point p;
    vec3 normal;
    double t;
};

class hittable {

public:
    // intersect if t in [t_min, t_max]
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};