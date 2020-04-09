#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "Base/CanvasObject.h"
#include "Utilities.h"

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
    Float3 backgroundColor;
    Float3 lineColor;
    std::vector<Float3> vertices;

    void render() override;
    Figure();

private:
    FigureType figureType;
};

#endif
