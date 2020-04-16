///Class representing a horizontal only slider, as
///Every other screen object, inherit the CanvasObject class
///And has a set of callbacks that it can override to use.
///It works by passing a minValue, a maxValue and the number
///of steps to interpolate between them, the tolerance is used for
///How much the mouse needs to move in order for a value change to be detected

#ifndef SLIDER_H
#define SLIDER_H

#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include <functional>
#include <vector>
#include "../Vectors/Float2.h"
#include "../Vectors/Float3.h"

class Slider : public CanvasObject
{
public:
    float handleSize;
    bool vertical;
    Float2 handlePosition;
    Float3 handleColor;

    Float3 backgroundColor0;
    Float3 backgroundColor1;

    float tolerance;
    float minValue;
    float maxValue;
    float curValue;
    float stepAmount;
    int steps;

    Slider(Float3 position, Float3 scale, Float3 backgroundColor, float handleSize, Float3 handleColor, bool vertical);
    Slider(Float3 position, Float3 scale, Float3 backgroundColor0, Float3 backgroundColor1, float handleSize, Float3 handleColor, bool vertical);
    void initializeSlider(float minValue, float maxValue, int steps, float tolerance);
    void render() override;
    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void addOnValueChangedListener(std::function<void(float value)> listener);
    void notifyOnValueChangedListeners();
    void setCurrentValue(float curValue);
    void generateBackgroundTexture();

private:
    Float3 *backgroundTexture;
    bool isDragging;
    float screenStep;
    int lastMouseState;
    Int2 prevMousePosition;
    std::vector<std::function<void(float value)>> onValueChangedListeners;
};

#endif
