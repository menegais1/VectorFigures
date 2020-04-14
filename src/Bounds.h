#ifndef BOUNDS_H
#define BOUNDS_H

#include "Base/ITransformable.h"
#include "Vectors/Float3.h"
#include <vector>

class Bounds : public ITransformable
{
public:
    Float3 center;
    Float3 minBound;
    Float3 maxBound;
    Float3 corners[4];
    Float3 extents;

    Bounds(Float3 minBound, Float3 maxBound);
    Bounds();
    void translate(Float3 translationAmount) override;
    void rotate(float angle, Float3 center) override;
    void rescale(Float3 scale, Float3 center) override;
};

#endif