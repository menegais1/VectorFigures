#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "Base/CanvasObject.h"
#include "Base/ITransformable.h"
#include "Vectors/Float2.h"
#include "Vectors/Float4.h"
#include "Bounds.h"

enum FigureType
{
    Square = 0,
    Triangle = 1,
    Circle = 2,
    Polygon = 3
};

class Figure : public CanvasObject, public ITransformable
{
public:
    Float3 backgroundColor;
    Float3 lineColor;
    Bounds bounds;
    std::vector<Float3> vertices;

    bool isSelected;
    bool drawBounds;
    Float4 highlightColor;

    void render() override;
    Figure(Float3 backgroundColor, Float3 lineColor, Float4 highlightColor, std::vector<Float3> vertices);
    Float3 getCenter();
    void translate(Float3 translationAmount) override;
    void rotate(float angle, Float3 center) override;
    void rescale(Float3 scale, Float3 center) override;

private:
    FigureType figureType;
    void initializeBounds();
};

#endif
