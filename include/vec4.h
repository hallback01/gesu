#pragma once

namespace gesu {
    /*
        A vector containing 4 floats
    */
    class Vec4 {

        public:

            Vec4();
            Vec4(float _v);
            Vec4(float _x, float _y, float _z, float _w);

            //operators
            Vec4 operator-(Vec4& other);

            /*
                Dot product
            */
            float operator*(Vec4& other);

            //instance functions
            float length();
            Vec4 normalized();

            //variables
            float x;
            float y;
            float z;
            float w;
        private:

    };
}
