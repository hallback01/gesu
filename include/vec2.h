#pragma once

/*
    A vector containing 3 floats
*/
class Vec2 {

    public:

        Vec2();
        Vec2(float _v);
        Vec2(float _x, float _y);

        //operators
        Vec2 operator-(Vec2& other);

        /*
            Dot product
        */
        float operator*(Vec2& other);

        //instance functions
        float length();
        Vec2 normalized();

        //variables
        float x;
        float y;
    private:

};