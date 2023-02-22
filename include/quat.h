#pragma once
#include "vec3.h"

namespace gesu {
    /*
        Quaternion
    */
    class Quat {

        public:

            Quat();
            Quat(float _w, float _x, float _y, float _z);

            //static construction functions
            static Quat from_euler(Vec3 euler_values);
            static Quat slerp(Quat qa, Quat qb, float t);

            //instance functions
            Vec3 to_euler();

            void normalize();

            //variables
            float w;
            float x;
            float y;
            float z;

        private:

    };
}
