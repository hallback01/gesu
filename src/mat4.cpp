#include <cstring>
#include <cmath>
#include "mat4.h"
#include "misc.h"

namespace gesu {
    Mat4::Mat4() {
        for(int y = 0; y < 4; y++) {
            for(int x = 0; x < 4; x++) {
                m_values[x][y] = 0.0;
            }
        }
        m_values[0][0] = 1.0;
        m_values[1][1] = 1.0;
        m_values[2][2] = 1.0;
        m_values[3][3] = 1.0;
    }

    float* Mat4::operator[](size_t i) {
        return m_values[i];
    }

    Mat4 Mat4::operator*(Mat4& other) {
        Mat4 multiplied;
        for(size_t y = 0; y < 4; y++) {
            for(size_t x = 0; x < 4; x++) {
                float m1 = other[x][0] * m_values[0][y];
                float m2 = other[x][1] * m_values[1][y];
                float m3 = other[x][2] * m_values[2][y];
                float m4 = other[x][3] * m_values[3][y];
                multiplied[x][y] = m1 + m2 + m3 + m4;
            }
        }
        return multiplied;
    }

    Mat4 Mat4::operator*(float rhs) {
        Mat4 multiplied;
        for(size_t y = 0; y < 4; y++) {
            for(size_t x = 0; x < 4; x++) {
                multiplied[x][y] *= rhs;
            }
        }
        return multiplied;
    }

    Mat4 Mat4::trs(Vec3 translation, Quat rotation, Vec3 scale) {


        Mat4 translation_rotation_matrix;
        Mat4 scale_matrix;
        
        memset(translation_rotation_matrix.m_values, 0, 16);
        memset(scale_matrix.m_values, 0, 16);
        
        //set translation
        translation_rotation_matrix[3][0] = translation.x;
        translation_rotation_matrix[3][1] = translation.y;
        translation_rotation_matrix[3][2] = translation.z;
        translation_rotation_matrix[3][3] = 1.0;

        //set rotation
        translation_rotation_matrix[0][0] = 1.0 - 2.0*rotation.y*rotation.y - 2.0*rotation.z*rotation.z;
        translation_rotation_matrix[0][1] = 2.0*rotation.x*rotation.y + 2.0*rotation.w*rotation.z;
        translation_rotation_matrix[0][2] = 2.0*rotation.x*rotation.z - 2.0*rotation.w*rotation.y;
        translation_rotation_matrix[1][0] = 2.0*rotation.x*rotation.y - 2.0*rotation.w*rotation.z;
        translation_rotation_matrix[1][1] = 1.0 - 2.0*rotation.x*rotation.x - 2.0*rotation.z*rotation.z;
        translation_rotation_matrix[1][2] = 2.0*rotation.y*rotation.z + 2.0*rotation.w*rotation.x;
        translation_rotation_matrix[2][0] = 2.0*rotation.x*rotation.z + 2.0*rotation.w*rotation.y;
        translation_rotation_matrix[2][1] = 2.0*rotation.y*rotation.z - 2.0*rotation.w*rotation.x;
        translation_rotation_matrix[2][2] = 1.0 - 2.0*rotation.x*rotation.x - 2.0*rotation.y*rotation.y;

        //set scale
        scale_matrix[0][0] = scale.x;
        scale_matrix[1][1] = scale.y;
        scale_matrix[2][2] = scale.z;
        scale_matrix[3][3] = 1.0;

        return translation_rotation_matrix * scale_matrix;
    }

    Mat4 Mat4::look_towards(Vec3 position, Vec3 look_direction, Vec3 up) {
        Vec3 nf = look_direction;
        Vec3 nu = up.normalized();
        Vec3 ns = Vec3::cross(nf, nu).normalized();
        nu = Vec3::cross(ns, nf);

        Mat4 view_matrix;
        view_matrix[0][0] = ns.x;
        view_matrix[1][0] = ns.y;
        view_matrix[2][0] = ns.z;
        view_matrix[0][1] = nu.x;
        view_matrix[1][1] = nu.y;
        view_matrix[2][1] = nu.z;
        view_matrix[0][2] = -nf.x;
        view_matrix[1][2] = -nf.y;
        view_matrix[2][2] = -nf.z;
        view_matrix[3][0] = -(ns * position);
        view_matrix[3][1] = -(nu * position);
        view_matrix[3][2] = nf * position;
        return view_matrix;
    }

    Mat4 Mat4::look_towards(Vec3 position, Quat look_direction, Vec3 up) {
        return Mat4::look_towards(position, look_direction.to_euler(), up);
    }

    Mat4 Mat4::look_at(Vec3 position, Vec3 look_position, Vec3 up) {
        Vec3 direction = look_position - position;
        return Mat4::look_towards(position, Quat::from_euler(direction.normalized()), up);
    }

    Mat4 Mat4::perspective(float fov, float aspect_ratio, float znear, float zfar) {

        float scale = std::tan(fov * 0.5);
        float right = aspect_ratio * scale;
        float left = -right;
        float top = scale;
        float bottom = -top;

        Mat4 perspective;
        perspective[0][0] = (2.0 * znear) / (right - left);
        perspective[0][1] = 0.0;
        perspective[0][2] = 0.0;
        perspective[0][3] = 0.0;
        perspective[1][0] = 0.0;
        perspective[1][1] = (2.0 * znear) / (top - bottom);
        perspective[1][2] = 0.0;
        perspective[1][3] = 0.0;
        perspective[2][0] = (right + left) / (right - left);
        perspective[2][1] = (top + bottom) / (top - bottom);
        perspective[2][2] = -(zfar + znear) / (zfar - znear);
        perspective[2][3] = -1.0;   
        perspective[3][0] = 0.0;
        perspective[3][1] = 0.0;
        perspective[3][2] = (-2.0 * zfar * znear) / (zfar - znear);
        perspective[3][3] = 0.0;
        return perspective;
    }

    Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float znear, float zfar) {

        float subx = right-left;
        float suby = top-bottom;
        float subz = zfar-znear;

        Mat4 orthographic;
        orthographic[0][0] = 2.0 / subx;
        orthographic[0][1] = 0.0;
        orthographic[0][2] = 0.0;
        orthographic[0][3] = 0.0;
        orthographic[1][0] = 0.0;
        orthographic[1][1] = 2.0 / suby;
        orthographic[1][2] = 0.0;
        orthographic[1][3] = 0.0;
        orthographic[2][0] = 0.0;
        orthographic[2][1] = 0.0;
        orthographic[2][2] = -2.0 / subz;
        orthographic[2][3] = 0.0;
        orthographic[3][0] = -(right + left) / subx;
        orthographic[3][1] = -(top + bottom) / suby;
        orthographic[3][2] = -(zfar + znear) / subz;
        orthographic[3][3] = 1.0;
        return orthographic;
    } 

    Mat4 Mat4::transpose(Mat4& matrix) {
        Mat4 transposed_matrix;
        transposed_matrix[0][0] = matrix[0][0];
        transposed_matrix[1][0] = matrix[0][1];
        transposed_matrix[2][0] = matrix[0][2];
        transposed_matrix[3][0] = matrix[0][3];
        transposed_matrix[0][1] = matrix[1][0];
        transposed_matrix[1][1] = matrix[1][1];
        transposed_matrix[2][1] = matrix[1][2];
        transposed_matrix[3][1] = matrix[1][3];
        transposed_matrix[0][2] = matrix[2][0];
        transposed_matrix[1][2] = matrix[2][1];
        transposed_matrix[2][2] = matrix[2][2];
        transposed_matrix[3][2] = matrix[2][3];
        transposed_matrix[0][3] = matrix[3][0];
        transposed_matrix[1][3] = matrix[3][1];
        transposed_matrix[2][3] = matrix[3][2];
        transposed_matrix[3][3] = matrix[3][3];
        return transposed_matrix;
    }

    Mat4 Mat4::adjoint(Mat4& matrix) {
        Mat4 adjoint_matrix;
        float a = matrix[0][0];
        float b = matrix[0][1];
        float c = matrix[0][2];
        float d = matrix[0][3];
        float e = matrix[1][0];
        float f = matrix[1][1];
        float g = matrix[1][2];
        float h = matrix[1][3];
        float i = matrix[2][0];
        float j = matrix[2][1];
        float k = matrix[2][2];
        float l = matrix[2][3];
        float m = matrix[3][0];
        float n = matrix[3][1];
        float o = matrix[3][2];
        float p = matrix[3][3];
        adjoint_matrix[0][0] = -h*k*n+g*l*n+h*j*o-f*l*o-g*j*p+f*k*p;
        adjoint_matrix[0][1] = d*k*n-c*l*n-d*j*o+b*l*o+c*j*p-b*k*p;
        adjoint_matrix[0][2] = -d*g*n+c*h*n+d*f*o-b*h*o-c*f*p+b*g*p;
        adjoint_matrix[0][3] = d*g*j-c*h*j-d*f*k+b*h*k+c*f*l-b*g*l;
        adjoint_matrix[1][0] = h*k*m-g*l*m-h*i*o+e*l*o+g*i*p-e*k*p;
        adjoint_matrix[1][1] = -d*k*m+c*l*m+d*i*o-a*l*o-c*i*p+a*k*p;
        adjoint_matrix[1][2] = d*g*m-c*h*m-d*e*o+a*h*o+c*e*p-a*g*p;
        adjoint_matrix[1][3] = -d*g*i+c*h*i+d*e*k-a*h*k-c*e*l+a*g*l;
        adjoint_matrix[2][0] = -h*j*m+f*l*m+h*i*n-e*l*n-f*i*p+e*j*p;
        adjoint_matrix[2][1] = d*j*m-b*l*m-d*i*n+a*l*n+b*i*p-a*j*p;
        adjoint_matrix[2][2] = -d*f*m+b*h*m+d*e*n-a*h*n-b*e*p+a*f*p;
        adjoint_matrix[2][3] = d*f*i-b*h*i-d*e*j+a*h*j+b*e*l-a*f*l;
        adjoint_matrix[3][0] = g*j*m-f*k*m-g*i*n+e*k*n+f*i*o-e*j*o;
        adjoint_matrix[3][1] = -c*j*m+b*k*m+c*i*n-a*k*n-b*i*o+a*j*o;
        adjoint_matrix[3][2] = c*f*m-b*g*m-c*e*n+a*g*n+b*e*o-a*f*o;
        adjoint_matrix[3][3] = -c*f*i+b*g*i+c*e*j-a*g*j-b*e*k+a*f*k;
        return adjoint_matrix;
    }

    Mat4 Mat4::inverse(Mat4& matrix) {
        Mat4 adjoint = Mat4::adjoint(matrix);
        float determinant = Mat4::determinant(matrix);
        return adjoint * (1.0 / determinant);
    }

    float Mat4::determinant(Mat4& matrix) {
        float det1 = matrix[0][0] * (matrix[1][1] * (matrix[2][2]*matrix[3][3]-matrix[2][3]*matrix[3][2]) + matrix[1][2]*(matrix[2][3]*matrix[3][1] - matrix[2][1]*matrix[3][3]) + matrix[1][3] * (matrix[2][1]*matrix[3][2]-matrix[2][2]*matrix[3][1]));
        float det2 = matrix[0][1] * (matrix[1][0] * (matrix[2][2]*matrix[3][3]-matrix[2][3]*matrix[3][2]) + matrix[1][2]*(matrix[2][3]*matrix[3][0] - matrix[2][0]*matrix[3][3]) + matrix[1][3] * (matrix[2][0]*matrix[3][2]-matrix[2][2]*matrix[3][0]));
        float det3 = matrix[0][2] * (matrix[1][0] * (matrix[2][1]*matrix[3][3]-matrix[2][3]*matrix[3][1]) + matrix[1][1]*(matrix[2][3]*matrix[3][1] - matrix[2][0]*matrix[3][3]) + matrix[1][3] * (matrix[2][0]*matrix[3][1]-matrix[2][1]*matrix[3][0]));
        float det4 = matrix[0][3] * (matrix[1][0] * (matrix[2][1]*matrix[3][2]-matrix[2][3]*matrix[3][1]) + matrix[1][1]*(matrix[2][2]*matrix[3][1] - matrix[2][0]*matrix[3][2]) + matrix[1][2] * (matrix[2][0]*matrix[3][1]-matrix[2][1]*matrix[3][0]));
        return det1 - det2 + det3 - det4;
    }

}
