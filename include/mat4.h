#pragma once
#include <stddef.h>
#include "quat.h"
#include "vec3.h"

namespace gesu {
    /*
        4x4 Matrix
    */
    class Mat4 {

        public:

            //identity matrix
            Mat4();

            //operators
            float* operator[](size_t i); 
            Mat4 operator*(Mat4& other);
            Mat4 operator*(float other);
            Vec4 operator*(Vec4 other);

            //static construction functions
            static Mat4 trs(Vec3 translation, Quat rotation, Vec3 scale);
            static Mat4 look_towards(Vec3 position, Quat look_direction, Vec3 up);
            static Mat4 look_towards(Vec3 position, Vec3 look_direction, Vec3 up);
            static Mat4 look_at(Vec3 position, Vec3 look_position, Vec3 up);
            static Mat4 perspective(float fov, float aspect_ratio, float znear, float zfar);
            static Mat4 orthographic(float left, float right, float bottom, float top, float znear = -100.0, float zfar = 100.0);

            //static functions that construct new matrices from already constructed matrices
            static Mat4 transpose(Mat4& matrix);
            static Mat4 adjoint(Mat4& matrix);
            static Mat4 inverse(Mat4& matrix);
            static float determinant(Mat4& matrix);

        private:
            float m_values[4][4];
    };
}