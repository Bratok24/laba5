#pragma once
#include "Point.h"
#include "Velocity.h"
#include "Color.h"

// Структура для визуального эффекта разлетающихся частиц
struct Dust {
    Point center;
    Velocity velocity;
    double lifetime;
    Color color;

    Dust(const Point& c, const Velocity& v, double life, const Color& col)
        : center(c), velocity(v), lifetime(life), color(col) {}
};