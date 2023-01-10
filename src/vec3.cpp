#include <cmath>
#include "vec3.h"

namespace gesu {
    Vec3::Vec3() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vec3::Vec3(float _v) {
        x = y = z = _v;
    }

    Vec3::Vec3(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    Vec3 Vec3::operator-(Vec3& other) {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vec3 Vec3::operator+(Vec3 other) {
        return {x + other.x, y + other.y, z + other.z};
    }


    Vec3 Vec3::operator-=(Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 Vec3::operator+=(Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3&Vec3:: operator*(float other) {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }

    float Vec3::operator*(Vec3& other) {
        return x*other.x + y*other.y + z*other.z;
    }

    Vec3 Vec3::cross(Vec3 a, Vec3 b) {
        return {
            a.y*b.z - a.z*b.y,
            a.z*b.x - a.x*b.z,
            a.x*b.y - a.y*b.x
        };
    }

    float Vec3::length() {
        return sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    }

    Vec3 Vec3::normalized() {
        float length = this->length();
        if(length > 0) {
            return {x / length, y / length, z / length};
        } else {
            return {0, 0, 0};
        }
    }
}