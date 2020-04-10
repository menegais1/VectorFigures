
#include <vector>
#include <iostream>
#include "Utilities.h"
#include "Canvas/gl_canvas2d.h"
#include "Figure.h"
void Figure::render()
{
    if (vertices.size() < 0)
        return;

    color(backgroundColor.x, backgroundColor.y, backgroundColor.z);
    polygonFill(vertices.data(), vertices.size());
    color(lineColor.x, lineColor.y, lineColor.z);
    polygon(vertices.data(), vertices.size());
    if (isSelected)
    {
        color(highlightColor.x, highlightColor.y, highlightColor.z, highlightColor.w);
        polygonFill(vertices.data(), vertices.size());
    }
}

Figure::Figure()
{
    isSelected = false;
}