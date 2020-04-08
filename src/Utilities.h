///Utilities file, has some common structs and functions used in the program

#ifndef UTILITIES_H
#define UTILITIES_H

enum Channel
{
    Red = 0,
    Green = 1,
    Blue = 2,
    Alpha = 3
};

enum MouseButton
{
    Left = 0,
    ScrollClick = 1,
    Right = 2,
    ScrollUp = 3,
    ScrollDown = 4
};

enum MouseState
{
    Down = 0,
    Up = 1,
    None = -2
};

class Color
{
public:
    unsigned char value[4];
};

typedef struct int2
{
    int x;
    int y;
} Int2;

typedef struct float2
{
    float x;
    float y;
} Float2;

typedef struct float3
{
    float x;
    float y;
    float z;
} Float3;

bool isPointInsideBounds(Float2 point, Float2 position, Float2 scale);
#endif
