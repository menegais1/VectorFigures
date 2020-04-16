#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include "../Base/CanvasObject.h"
#include "../Vectors/Float3.h"
#include <vector>
class ColorSlider : public CanvasObject
{
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void render() override;
    void setColors(Float3 bottomColor, Float3 topColor);
    ColorSlider(Float3 position, int width, int height);
    Float3 currentSample;

private:
    int width;
    int height;
    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float3 *texture;
    Float3 topColor;
    Float3 bottomColor;

    void generateTexture();
    Float3 sampleTexture(Float2 position);
};

#endif