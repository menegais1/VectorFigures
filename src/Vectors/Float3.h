#ifndef FLOAT3_H
#define FLOAT3_H

#include "Float2.h"

class Float3
{
public:
    float x, y, z;

    float length();
    Float3 unit();
    Float3(Float2, float);
    Float3(float, float, float);
    Float3();
    Float3 operator+(const Float3 &);
    Float3 operator*(const float);
};

#endif