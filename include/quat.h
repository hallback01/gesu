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

            //instance functions
            Vec3 to_euler();

            //variables
            float w;
            float x;
            float y;
            float z;

        private:

    };
}
