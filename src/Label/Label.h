///Class used to display a text label with background color

#ifndef LABEL_H
#define LABEL_H

#include "../Base/CanvasObject.h"
#include "string"
class Label : public CanvasObject
{
public:
    std::string title;
    Float3 textColor;
    Float3 backgroundColor;
    Label(Float2 position, Float2 scale, Float3 textColor, Float3 backgroundColor, std::string title);
    void render() override;
};

#endif