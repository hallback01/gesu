#include <cmath>
#include "vec4.h"

namespace gesu {
    Vec4::Vec4() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        w = 0.0;
    }

    Vec4::Vec4(float _v) {
        x = _v;
        y = _v;
        z = _v;
        w = _v;
    }

    Vec4::Vec4(float _x, float _y, float _z, float _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    Vec4 Vec4::operator-(Vec4& other) {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    float Vec4::operator*(Vec4& other) {
        return x*other.x + y*other.y + z*other.z + w*other.w;
    }

    Vec4& Vec4::operator*(float other) {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        this->w *= other;
        return *this;
    }

    float Vec4::length() {
        return sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2));
    }

    Vec4 Vec4::normalized() {
        float length = this->length();
        return {x / length, y / length, z / length, w / length};
    }
}