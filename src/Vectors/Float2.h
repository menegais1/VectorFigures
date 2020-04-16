#ifndef FLOAT2_H
#define FLOAT2_H


class Float2
{
public:
    float x, y;

    float length();
    Float2 unit();
    Float2(float, float);
    Float2();
    Float2 operator+(const Float2 &);
    Float2 operator-(const Float2 &);
    Float2 operator*(const float);
};

#endif