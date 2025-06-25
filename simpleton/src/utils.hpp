#pragma once

namespace Simpleton {
    template <typename T>
    struct Point
    {
        T x, y;
    };

    template <typename T>
    struct Color
    {
        T r, g, b, a;
    };

    template <typename T>
    struct Rect 
    {
        T x, y;
        T w, h;
    };

    template <typename T>
    struct Circle
    {
        T x, y;
        T radius;
    };
}