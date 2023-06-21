#include <cmath>
#include "vec2.h"

namespace gesu {
    Vec2::Vec2() {
        x = 0;
        y = 0;
    }

    Vec2::Vec2(float _v) {
        x = _v;
        y = _v;
    }

    Vec2::Vec2(float _x, float _y) {
        x = _x;
        y = _y;
    }

    Vec2 Vec2::operator-(Vec2 other) {
        return {x - other.x, y - other.y};
    }

    Vec2 Vec2::operator+(Vec2 other) {
        return {x + other.x, y + other.y};
    }

    float Vec2::operator*(Vec2 other) {
        return x*other.x + y*other.y;
    }

    float Vec2::length() {
        return sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    Vec2 Vec2::normalized() {
        float length = this->length();
        if(length > 0) {
            return {x / length, y / length};
        } else {
            return {0, 0};
        }
    }
}
