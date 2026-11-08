#include "World.h"
#include "Painter.h"
#include <fstream>
#include <cmath>
#include <cstdlib> 

static constexpr double timePerTick = 0.001;

World::World(const std::string& worldFilePath) {
    std::ifstream stream(worldFilePath);
    
    // ПУНКТ 2: Читаем границы мира напрямую в Point
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    Point center;
    Velocity velocity;
    Color color;
    double radius;
    bool isCollidable;

    while (stream.peek(), stream.good()) {
        // ПУНКТ 2: Читаем объекты напрямую (x,y), (vx,vy) и (r,g,b)
        stream >> center >> velocity >> color >> radius >> std::boolalpha >> isCollidable;
        
        // ПУНКТ 1: Создаем шар и добавляем в вектор
        balls.emplace_back(center, velocity, color, radius, isCollidable);
    }
}

void World::show(Painter& painter) const {
    // Рисуем границы
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Рисуем шары
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
    
    // ПУНКТ 4: Рисуем частицы пыли
    for (const Dust& dust : dusts) {
        painter.draw(dust.center, 2.0, dust.color); // Радиус пылинки 2.0
    }
}

void World::update(double time) {
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    // Сюда физика будет складывать координаты столкновений
    std::vector<Point> collisionPoints;
    
    // ПУНКТ 3: Передаем вектор для сбора точек
    physics.update(balls, ticks, &collisionPoints);

    // ПУНКТ 4: Спавним пыль в местах столкновений
    for (const Point& p : collisionPoints) {
        for (int i = 0; i < 5; ++i) { // 5 частиц на одно столкновение
            double angle = (std::rand() % 360) * 3.14159265 / 180.0;
            double speed = 20.0 + (std::rand() % 50); // случайная скорость
            Point v(std::cos(angle) * speed, std::sin(angle) * speed);
            // Время жизни 0.5 секунд, цвет - оранжевый (1, 0.5, 0)
            dusts.emplace_back(p, Velocity(v), 0.5, Color(1, 0.5, 0));
        }
    }

    // ПУНКТ 4: Обновляем и удаляем мертвую пыль
    for (auto it = dusts.begin(); it != dusts.end(); ) {
        // Двигаем частицу (игнорируя физику)
        it->center = it->center + it->velocity.vector() * time;
        // Уменьшаем время жизни
        it->lifetime -= time;

        // Удаляем, если время вышло
        if (it->lifetime <= 0) {
            it = dusts.erase(it);
        } else {
            ++it;
        }
    }
}