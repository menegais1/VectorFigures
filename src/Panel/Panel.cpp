#include "Panel.h"
#include <iostream>

Panel::Panel(std::vector<CanvasObject *> &children)
{
    this->children = children;
}
Panel::Panel(Float3 position, Float3 scale, Float3 backgroundColor)
{
    this->position = position;
    this->scale = scale;
    this->backgroundColor = backgroundColor;
}
void Panel::setActive(bool isActive)
{
    for (int i = 0; i < children.size(); i++)
    {
        children[i]->setActive(isActive);
    }
};

Panel::Panel()
{
}
