#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"

class Ball {
public:
    // добавил конструктор для удобного создания шаров
    Ball(const Point& center, const Velocity& velocity, const Color& color, double radius, bool isCollidable);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    
    // Новый метод нужен физике для проверки "призрачности"
    bool getIsCollidable() const; 

private:
    Point m_center;
    Velocity m_velocity;
    Color m_color;
    double m_radius;
    double m_mass;
    bool m_isCollidable;
};