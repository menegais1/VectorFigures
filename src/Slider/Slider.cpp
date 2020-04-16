#include "Slider.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
#include <cstdlib>
#include <iostream>
#include "../Vectors/Float2.h"
#include "../Vectors/Float3.h"

Slider::Slider(Float3 position, Float3 scale, Float3 backgroundColor, float handleSize, Float3 handleColor, bool vertical) : CanvasObject()
{
    this->position = position;
    this->scale = scale;
    this->backgroundColor0 = backgroundColor;
    this->handleSize = handleSize;
    this->handleColor = handleColor;
    this->lastMouseState = MouseState::None;
    this->vertical = vertical;
    if (vertical)
    {
        this->handlePosition = {this->position.x + scale.x / 2, this->position.y};
    }
    else
    {
        this->handlePosition = {this->position.x, this->position.y + scale.y / 2};
    }
}

Slider::Slider(Float3 position, Float3 scale, Float3 backgroundColor0, Float3 backgroundColor1, float handleSize, Float3 handleColor, bool vertical) : CanvasObject()
{
    this->position = position;
    this->scale = scale;
    this->backgroundColor0 = backgroundColor0;
    this->backgroundColor1 = backgroundColor1;
    this->handleSize = handleSize;
    this->handleColor = handleColor;
    this->lastMouseState = MouseState::None;
    this->vertical = vertical;
    if (vertical)
    {
        this->handlePosition = {this->position.x + scale.x / 2, this->position.y};
    }
    else
    {
        this->handlePosition = {this->position.x, this->position.y + scale.y / 2};
    }
}
void Slider::initializeSlider(float minValue, float maxValue, int steps, float tolerance)
{
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->steps = steps;
    this->tolerance = tolerance;
    curValue = minValue;
    if (vertical)
    {
        screenStep = (position.y + scale.y - position.y) / steps;
    }
    else
    {
        screenStep = (position.x + scale.x - position.x) / steps;
    }
    stepAmount = (maxValue - minValue) / steps;
}
void Slider::render()
{
    color(backgroundColor0.x, backgroundColor0.y, backgroundColor0.z);
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
    float mouseDelta = 0;
    if (vertical)
    {
        if (y - prevMousePosition.y > 0)
            direction = 1;
        else if (y - prevMousePosition.y < 0)
            direction = -1;
        mouseDelta = abs(y - handlePosition.y);
    }
    else
    {
        if (x - prevMousePosition.x > 0)
            direction = 1;
        else if (x - prevMousePosition.x < 0)
            direction = -1;
        mouseDelta = abs(x - handlePosition.x);
    }

    if (state == MouseState::None &&
        this->lastMouseState == MouseState::Down &&
        (isPointInside || isDragging) &&
        mouseDelta > tolerance &&
        direction != 0)
    {
        isDragging = true;
        if (curValue >= maxValue && direction > 0)
        {
            curValue = maxValue;
            if (vertical)
            {

                handlePosition.y = position.y + scale.y;
            }
            else
            {

                handlePosition.x = position.x + scale.x;
            }
        }
        else if (curValue <= minValue && direction < 0)
        {
            curValue = minValue;
            if (vertical)
            {
                handlePosition.y = position.y;
            }
            else
            {
                handlePosition.x = position.x;
            }
        }
        else
        {
            if (vertical)
            {
                handlePosition.y += screenStep * direction;
            }
            else
            {

                handlePosition.x += screenStep * direction;
            }
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
    if (vertical)
    {
        this->handlePosition.y = (position.y + scale.y) - ((maxValue - curValue) / this->stepAmount) * screenStep;
    }
    else
    {
        this->handlePosition.x = (position.x + scale.x) - ((maxValue - curValue) / this->stepAmount) * screenStep;
    }
}

void Slider::generateBackgroundTexture()
{
    for (size_t i = 0; i < 1; i+=0)
    {
        /* code */
    }
    
}