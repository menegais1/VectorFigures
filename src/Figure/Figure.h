#ifndef FIGURE_H
#define FIGURE_H

#include <vector>
#include "../Base/CanvasObject.h"
#include "../Base/ITransformable.h"
#include "../Vectors/Float2.h"
#include "../Vectors/Float4.h"
#include "../Bounds/Bounds.h"

class Figure : public CanvasObject {
public:
    Figure();

    Float3 backgroundColor;
    Float3 lineColor;
    Bounds bounds;
    std::vector<Float3> vertices;

    bool isSelected;
    bool drawBounds;
    Float4 highlightColor;

    void render() override;

    Figure(Float3 backgroundColor, Float3 lineColor, Float4 highlightColor, std::vector<Float3> vertices);

    ~Figure() = default;

    Float3 getCenter();

    void translate(Float3 translationAmount) override;

    void rotate(float angle, Float3 center) override;

    void rescale(Float3 scale, Float3 center) override;

    bool pointIntersectsObject(Float3 point) override;

private:

    void initializeBounds();

};

#endif
