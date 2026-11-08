#pragma once
#include "Ball.hpp"
#include "Physics.h"
#include "Dust.h"
#include <vector>
#include <string>

class Painter;

class World {
public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);

private:
    Point topLeft;
    Point bottomRight;
    Physics physics;
    std::vector<Ball> balls;
    std::vector<Dust> dusts; // ПУНКТ 4: Вектор для хранения частиц
    double restTime = 0.0;
};