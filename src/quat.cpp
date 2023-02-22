#include <cmath>
#include "quat.h"
#include "misc.h"

namespace gesu {
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

    Quat Quat::slerp(Quat q1, Quat q2, float t) {
        double cos_half_theta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
        if (abs(cos_half_theta) >= 1.0){
            return Quat(q1.w, q1.x, q1.y, q1.z);
        }

        double half_theta = acos(cos_half_theta);
        double sinhalf_theta = sqrt(1.0 - cos_half_theta*cos_half_theta);
        if (fabs(sinhalf_theta) < 0.001){
            return Quat(q1.w * 0.5 + q2.w * 0.5, q1.x * 0.5 + q2.x * 0.5, q1.y * 0.5 + q2.y * 0.5, q1.z * 0.5 + q2.z * 0.5);
        }

        double ratio_1 = sin((1 - t) * half_theta) / sinhalf_theta;
        double ratio_2 = sin(t * half_theta) / sinhalf_theta; 
        return Quat(q1.w * ratio_1 + q2.w * ratio_2, q1.x * ratio_1 + q2.x * ratio_2, q1.y * ratio_1 + q2.y * ratio_2, q1.z * ratio_1 + q2.z * ratio_2);
    }

    void Quat::normalize() {
        float norm = sqrt(x*x + y*y + z*z + w*w);
        x /= norm;
        y /= norm;
        z /= norm;
        w /= norm;
    }
}