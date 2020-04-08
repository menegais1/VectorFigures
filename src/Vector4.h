#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4
{
public:
    double x;
    double y;
    double z;
    double w;

    double &operator[](int index);
    Vector4(double x = 0, double y = 0, double z = 0, double w = 1);
};

#endif
