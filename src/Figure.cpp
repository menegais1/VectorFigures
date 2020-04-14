
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

void Figure::calculateCenter()
{
    Float3 mean = {0, 0, 0};
    for (int i = 0; i < vertices.size(); i++)
    {
        mean.x += vertices[i].x;
        mean.y += vertices[i].y;
        mean.z += vertices[i].z;
    }
    this->center = {mean.x / vertices.size(),
                    mean.y / vertices.size(),
                    mean.z / vertices.size()};
}

void Figure::translate(Float3 translationAmount)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].x += translationAmount.x;
        vertices[i].y += translationAmount.y;
        vertices[i].z += translationAmount.z;
    }
}

Figure::Figure(Float3 backgroundColor, Float3 lineColor, Float4 highlightColor, std::vector<Float3> vertices)
{
    this->backgroundColor = backgroundColor;
    this->lineColor = lineColor;
    this->highlightColor = highlightColor;
    this->vertices = vertices;
    calculateCenter();
    isSelected = false;
}
