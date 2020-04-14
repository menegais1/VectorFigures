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
    Float3 center;
    std::vector<Float3> vertices;

    bool isSelected;
    Float4 highlightColor;

    void render() override;
    Figure(Float3 backgroundColor, Float3 lineColor, Float4 highlightColor, std::vector<Float3> vertices);

    void translate(Float3 translationAmount);
    void rotation(float angle, Float3 center);
    void rescale(Float2 scale, Float3 center);

private:
    FigureType figureType;
    void calculateCenter();
};

#endif
