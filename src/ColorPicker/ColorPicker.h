#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "../Base/CanvasObject.h"
#include "../Vectors/Float3.h"
#include <vector>
class ColorPicker : public CanvasObject
{
public:
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void render() override;
    ColorPicker(Float3 position, int width, int height);
    Float3 currentSample;

private:
    int width;
    int height;
    bool mouseDragging;
    bool mouseInside;
    Float2 currentMousePosition;
    Float3 *texture;
    std::vector<Float3> topVertices;
    std::vector<Float3> bottomVertices;

    void generateTexture();
    Float3 sampleTexture(Float2 position);
};

#endif