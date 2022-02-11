#pragma once

#include "mathlib.hpp"

class ray {

private:
    // P(t) = A + tB
    point ori;
    vec3 dir;

public:
    ray(point _ori, vec3 _dir): ori(_ori), dir(_dir) {}

    void set_origin(point p) { ori = p; }
    void set_direction(vec3 _dir) { dir = _dir; }

    point get_origin() const { return ori; }
    vec3 get_direction() const { return dir; }
    
    point get_point(double t) const {
        return ori + t * dir;
    }

};