#include "Ball.hpp"
#include <cmath>

// Конструктор: сохраняем все переданные значения и вычисляем массу
Ball::Ball(const Point& center, const Velocity& velocity, const Color& color, double radius, bool isCollidable)
    : m_center(center), m_velocity(velocity), m_color(color), 
      m_radius(radius), m_isCollidable(isCollidable) {
    
    // Масса вычисляется по формуле из исходного zip: 4/3 * pi * r^3
    const double PI = 3.14159265358979323846;
    m_mass = (4.0 / 3.0) * PI * std::pow(m_radius, 3);
}

void Ball::setVelocity(const Velocity& velocity) {
    m_velocity = velocity;
}

Velocity Ball::getVelocity() const {
    return m_velocity;
}

void Ball::draw(Painter& painter) const {
    // Отрисовываем круг, передаем центр, радиус и цвет
    painter.draw(m_center, m_radius, m_color);
}

void Ball::setCenter(const Point& center) {
    m_center = center;
}

Point Ball::getCenter() const {
    return m_center;
}

double Ball::getRadius() const {
    return m_radius;
}

double Ball::getMass() const {
    return m_mass;
}

bool Ball::getIsCollidable() const {
    return m_isCollidable;
}