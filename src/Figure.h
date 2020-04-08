#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "Base/CanvasObject.h"
#include "Vector4.h"
enum FigureType
{
    Square = 0,
    Triangle = 1,
    Circle = 2,
    Polygon = 3
};

class Figure : public CanvasObject
{
public:
    Vector4 backgroundColor;
    Vector4 lineColor;
    vector<Vector4> vertices;
    int zIndex;
    
    void render() override;

private:
    FigureType figureType;
}

#endif
