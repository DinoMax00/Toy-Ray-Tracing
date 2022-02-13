#pragma once

#include <cmath>
#include <iostream>
#include <assert.h>


class vec3 {

public:
    double x, y, z;

    vec3() { x = y = z = 0; }
    vec3(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}

    // override operators
    vec3 operator - () const {
        return vec3(-x, -y, -z);
    }

    vec3& operator += (const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3& operator -= (const vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    vec3& operator *= (const double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    double operator *= (const vec3& v) {
        return x * v.x + y * v.y + z * v.z;
    }

    vec3& operator /= (const double t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    friend std::ostream& operator << (std::ostream& out, const vec3& v) {
        return out << v.x << " " << v.y << " " << v.z;
    }

    friend vec3 operator + (const vec3& u, const vec3& v) {
        return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
    }

    friend vec3 operator - (const vec3& u, const vec3& v) {
        return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
    }

    friend double operator * (const vec3& u, const vec3& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    friend vec3 operator * (const vec3& u, const double t) {
        return vec3(u.x * t, u.y * t, u.z * t);
    }

    friend vec3 operator * (const double t, const vec3& u) {
        return vec3(u.x * t, u.y * t, u.z * t);
    }

    friend vec3 operator / (const vec3& u, const double t) {
        return vec3(u.x / t, u.y / t, u.z / t);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    bool near_zero() const {
        constexpr double eps = 1e-8;
        return (fabs(x) < eps) && (fabs(y) < eps) && (fabs(z) < eps);
    }
};

// alias
using color = vec3;
using point = vec3;

// functions
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline vec3 normalize(vec3 v) {
    double t = v.length();
    return v / t;
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (in_unit_sphere * normal > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * v * n * n;
}

vec3 inner_mult(const vec3& u, const vec3& v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vec3 refract(const vec3& r, const vec3& normal, double n) {
    double cos_theta = fmin(-r * normal, 1.0);
    vec3 r_perp = n * (r + cos_theta * normal);
    vec3 r_parallel = -sqrt(fabs(1.0 - r_perp.length() * r_perp.length())) * normal;
    return r_perp + r_parallel;
}
