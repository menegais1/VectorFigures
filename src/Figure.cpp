
#include <vector>
#include <iostream>
#include <cmath>
#include "Vectors/Float2.h"
#include "Vectors/Float4.h"
#include "Canvas/gl_canvas2d.h"
#include "Figure.h"
#include "Bounds.h"
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

    if (drawBounds)
    {
        line(bounds.corners[0].x, bounds.corners[0].y, bounds.corners[1].x, bounds.corners[1].y);
        line(bounds.corners[1].x, bounds.corners[1].y, bounds.corners[2].x, bounds.corners[2].y);
        line(bounds.corners[2].x, bounds.corners[2].y, bounds.corners[3].x, bounds.corners[3].y);
        line(bounds.corners[3].x, bounds.corners[3].y, bounds.corners[0].x, bounds.corners[0].y);
    }
}

Float3 Figure::getCenter()
{
    return bounds.center;
}
void Figure::translate(Float3 translationAmount)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i].x += translationAmount.x;
        vertices[i].y += translationAmount.y;
        vertices[i].z += translationAmount.z;
    }
    bounds.translate(translationAmount);
}

void Figure::rotate(float angle, Float3 center)
{
    translate({-center.x, -center.y, 0});
    for (int i = 0; i < vertices.size(); i++)
    {
        float x = vertices[i].x * cos(angle) - vertices[i].y * sin(angle);
        float y = vertices[i].x * sin(angle) + vertices[i].y * cos(angle);
        vertices[i].x = x;
        vertices[i].y = y;
    }
    translate({center.x, center.y, 0});
    bounds.rotate(angle, center);
}

void Figure::rescale(Float3 scale, Float3 center)
{
    translate({-center.x, -center.y, 0});
    for (int i = 0; i < vertices.size(); i++)
    {
        float x = vertices[i].x * (scale.x + 1);
        float y = vertices[i].y * (scale.y + 1);
        vertices[i].x = x;
        vertices[i].y = y;
    }
    translate({center.x, center.y, 0});
    bounds.rescale(scale, center);
}

void Figure::initializeBounds()
{
    Float3 minBound;
    Float3 maxBound;
    float minX = vertices[0].x, minY = vertices[0].y, maxX = vertices[0].x, maxY = vertices[0].y;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].x < minX)
            minX = vertices[i].x;
        if (vertices[i].x > maxX)
            maxX = vertices[i].x;
        if (vertices[i].y < minY)
            minY = vertices[i].y;
        if (vertices[i].y > maxY)
            maxY = vertices[i].y;
    }
    minBound = {minX, minY, 0};
    maxBound = {maxX, maxY, 0};
    bounds = {minBound, maxBound};
}
Figure::Figure(Float3 backgroundColor, Float3 lineColor, Float4 highlightColor, std::vector<Float3> vertices)
{
    this->backgroundColor = backgroundColor;
    this->lineColor = lineColor;
    this->highlightColor = highlightColor;
    this->vertices = vertices;
    initializeBounds();
    isSelected = false;
    drawBounds = false;
}
