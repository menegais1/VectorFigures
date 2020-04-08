#include "Slider.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
#include <cstdlib>
#include <iostream>

Slider::Slider(Float2 position, Float2 scale, Float3 backgroundColor, float handleSize, Float3 handleColor) : CanvasObject()
{
    this->position = position;
    this->scale = scale;
    this->backgroundColor = backgroundColor;
    this->handleSize = handleSize;
    this->handleColor = handleColor;
    this->lastMouseState = MouseState::None;
    this->handlePosition = {this->position.x, this->position.y + scale.y / 2};
}
void Slider::initializeSlider(float minValue, float maxValue, int steps, float tolerance)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->steps = steps;
    this->tolerance = tolerance;
    curValue = minValue;
    screenStep = (position.x + scale.x - position.x) / steps;
    stepAmount = (maxValue - minValue) / steps;
}
void Slider::render()
{
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rect(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(handleColor.x, handleColor.y, handleColor.z);
    circleFill(handlePosition.x, handlePosition.y, handleSize, 30);
}
void Slider::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    bool isPointInside = isPointInsideBounds({x, y}, {handlePosition.x - handleSize, handlePosition.y - handleSize}, {handleSize * 2, handleSize * 2});
    if ((state == MouseState::Down && button == MouseButton::Left && isPointInside) ||
            state == MouseState::Up)
    {
        this->lastMouseState = state;
        isDragging = false;
    }

    direction = 0;
    if (x - prevMousePosition.x > 0)
        direction = 1;
    else if (x - prevMousePosition.x < 0)
        direction = -1;

    if (state == MouseState::None &&
        this->lastMouseState == MouseState::Down &&
        (isPointInside || isDragging) &&
        abs(x - handlePosition.x) > tolerance &&
        direction != 0)
    {
        isDragging = true;
        if (curValue >= maxValue && direction > 0)
        {
            curValue = maxValue;
            handlePosition.x = position.x + scale.x;
        }
        else if (curValue <= minValue && direction < 0)
        {
            curValue = minValue;
            handlePosition.x = position.x;
        }
        else
        {
            handlePosition.x += screenStep * direction;
            curValue += stepAmount * direction;
            if (curValue < minValue)
                curValue = minValue;
            if (curValue > maxValue)
                curValue = maxValue;
            notifyOnValueChangedListeners();
        }
    }

    prevMousePosition = {x, y};
}
void Slider::addOnValueChangedListener(std::function<void(float value)> listener)
{
    onValueChangedListeners.push_back(listener);
}
void Slider::notifyOnValueChangedListeners()
{
    for (int i = 0; i < onValueChangedListeners.size(); i++)
    {
        onValueChangedListeners[i](curValue);
    }
}

void Slider::setCurrentValue(float curValue)
{
    this->curValue = curValue;
    this->handlePosition.x = (position.x + scale.x) - ((maxValue - curValue) / this->stepAmount) * screenStep;
}
