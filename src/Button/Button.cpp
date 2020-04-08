#include <vector>
#include <functional>
#include <iostream>

#include "Button.h"
#include "../Base/CanvasObject.h"
#include "../Utilities.h"
#include "../Canvas/gl_canvas2d.h"
using namespace std;

Button::Button(Float2 position, Float2 scale, Float3 backgroundColor, string title, Float3 textColor) : CanvasObject(), backgroundColor(backgroundColor),
                                                                                                        title(title),
                                                                                                        textColor(textColor)
{
    this->position = position;
    this->scale = scale;
}
void Button::mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (button == MouseButton::Left && state == MouseState::Down)
    {
        if (isPointInsideBounds({x, y}, position, scale))
        {
            notifyOnClickListeners();
        }
    }
}
void Button::render()
{
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(textColor.x, textColor.y, textColor.z);
    text(position.x + 10, position.y + scale.y / 2, title.c_str());
}

void Button::notifyOnClickListeners()
{
    for (int i = 0; i < onClickListeners.size(); i++)
    {
        onClickListeners[i]();
    }
}

void Button::addListener(std::function<void()> listener)
{
    onClickListeners.push_back(listener);
}
