#include "Utilities.h"
bool isPointInsideBounds(Float2 point, Float2 position, Float2 scale)
{
    return point.x < position.x + scale.x && point.x > position.x && point.y < position.y + scale.y && point.y > position.y;
}
