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
