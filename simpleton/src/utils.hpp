#pragma once

namespace Simpleton {
    typedef struct Point
    {
        int x;
        int y;
    } Point;

    typedef struct Color 
    {
        float r, g, b, a;
    } Color;

    typedef struct Rect 
    {
        Point pos;
        int w, h;
    } Rect;
}