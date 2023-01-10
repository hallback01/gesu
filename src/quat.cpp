#include <cmath>
#include "quat.h"
#include "misc.h"

Quat::Quat() {
    w = 1.0;
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Quat::Quat(float _w, float _x, float _y, float _z) {
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

Quat Quat::from_euler(Vec3 euler_values) {
    float w =  std::cos(euler_values.x/2.0)*std::cos(euler_values.y/2.0)*std::cos(euler_values.z/2.0) + std::sin(euler_values.x/2.0)*std::sin(euler_values.y/2.0)*std::sin(euler_values.z/2.0);
    float x = -std::cos(euler_values.x/2.0)*std::sin(euler_values.y/2.0)*std::cos(euler_values.z/2.0) - std::sin(euler_values.x/2.0)*std::cos(euler_values.y/2.0)*std::sin(euler_values.z/2.0);
    float y =  std::cos(euler_values.x/2.0)*std::sin(euler_values.y/2.0)*std::sin(euler_values.z/2.0) - std::sin(euler_values.x/2.0)*std::cos(euler_values.y/2.0)*std::cos(euler_values.z/2.0);
    float z =  std::sin(euler_values.x/2.0)*std::sin(euler_values.y/2.0)*std::cos(euler_values.z/2.0) - std::cos(euler_values.x/2.0)*std::cos(euler_values.y/2.0)*std::sin(euler_values.z/2.0);
    return {w, x, y, z};
}

Vec3 Quat::to_euler() {
    float sp = -2.0 * (y*z - w*x);
    if(abs(sp) > 0.9999) {
        float p = Misc::PI / 2.0 * sp;
        float h = std::atan2(-x*z - w*y, 0.5 - y*y - z*z);
        float b = 0.0;
        return {h, p, b};
    } else {
        float p = std::asin(sp);
        float h = std::atan2(x*z - w*y, 0.5 - x*x - y*y);
        float b = std::atan2(x*y - w*z, 0.5 - x*x - z*z);
        return {h, p, b};
    }
}