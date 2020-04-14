#ifndef ITRANSFORMABLE_H
#define ITRANSFORMABLE_H

class ITransformable
{
public:
    virtual void translate(Float3) = 0;
    virtual void rotate(float, Float3) = 0;
    virtual void rescale(Float3, Float3) = 0;
};
#endif
