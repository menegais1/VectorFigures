#include "Label.h"
#include "string"
#include "../Canvas/gl_canvas2d.h"

Label::Label(Float2 position, Float2 scale, Float3 textColor, Float3 backgroundColor, std::string title)
{
    this->position = position;
    this->scale = scale;
    this->textColor = textColor;
    this->backgroundColor = backgroundColor;
    this->title = title;
}

void Label::render()
{
    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    rectFill(position.x, position.y, position.x + scale.x, position.y + scale.y);
    color(textColor.x, textColor.y, textColor.z);
    text(position.x, position.y + scale.y / 4,title.c_str());
}