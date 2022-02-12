#pragma once

#include "ray.hpp"

/// An Abstraction for hittable objects

class hit_record {

public:
    point p; // intersection
    vec3 normal; // normal direction, always against the ray direction
    double t; // record the ray information
    bool front_face; // true if the ray come from the outside to inside

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = (r.get_direction() * outward_normal) < 0;
        normal = front_face? outward_normal: -outward_normal;
    }
};

class hittable {

public:
    // intersect if t in [t_min, t_max]
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};