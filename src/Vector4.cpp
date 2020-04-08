#include "Vector4.h"

double &Vector4::operator[](int index)
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    if (index == 2)
        return z;
    if (index == 3)
        return w;
}

Vector4::Vector4(double x, double y, double z, double w = 1) : x(x), y(y), z(z), w(w)
{
}
