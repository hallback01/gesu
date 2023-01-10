#pragma once
#include "vec2.h"

/*
    A vector containing 3 floats
*/
class Vec3 {

    public:

        Vec3();
        Vec3(float _v);
        Vec3(float _x, float _y, float _z);

        //operators
        Vec3 operator-(Vec3& other);
        Vec3 operator+(Vec3 other);
        Vec3 operator-=(Vec3& other);
        Vec3 operator+=(Vec3& other);
        Vec3& operator*(float other);

        /*
            Dot product
        */
        float operator*(Vec3& other);

        //static construction functions
        static Vec3 cross(Vec3 a, Vec3 b);

        //instance functions
        float length();
        Vec3 normalized();
        inline Vec2 xy() { return {x, y};}
        inline Vec2 xz() { return {x, z};}
        inline Vec2 yx() { return {y, x};}
        inline Vec2 yz() { return {y, z};}
        inline Vec2 zx() { return {z, x};}
        inline Vec2 zy() { return {z, y};}

        //variables
        float x;
        float y;
        float z;
    private:

};