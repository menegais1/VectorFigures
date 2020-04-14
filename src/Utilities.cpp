#include "Utilities.h"
#include <vector>
#include <cstdlib>
#include <cmath>
bool isPointInsideBounds(Float2 point, Float2 position, Float2 scale)
{
    return point.x < position.x + scale.x && point.x > position.x && point.y < position.y + scale.y && point.y > position.y;
}

int isLeft(Float3 P0, Float3 P1, Float3 P2)
{
    return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
}

bool isPointInsidePolygon(Float3 P, std::vector<Float3> vertices, int n)
{
    int cn = 0; // the  crossing number counter

    // loop through all edges of the polygon
    for (int i = 0; i < n; i++)
    {                                                             // edge from V[i]  to V[i+1]
        if (((vertices[i].y <= P.y) && (vertices[i + 1].y > P.y)) // an upward crossing
            || ((vertices[i].y > P.y) && (vertices[i + 1].y <= P.y)))
        { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P.y - vertices[i].y) / (vertices[i + 1].y - vertices[i].y);
            if (P.x < vertices[i].x + vt * (vertices[i + 1].x - vertices[i].x)) // P.x < intersect
                ++cn;                                                           // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn & 1); // 0 if even (out), and 1 if  odd (in)
}

bool leftMouseDown(int button, int state)
{
    return button == MouseButton::Left && state == MouseState::Down;
}

bool leftMouseUp(int button, int state)
{
    return button == MouseButton::Left && state == MouseState::Up;
}

float Float2::length()
{
    return std::sqrt(x * x + y * y);
}