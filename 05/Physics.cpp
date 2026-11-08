#include "Physics.h"
#include <cmath>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

// Обновленный метод update с приемом вектора точек столкновений
void Physics::update(std::vector<Ball>& balls, const size_t ticks, std::vector<Point>* collisionPoints) const {
    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls, collisionPoints);
    }
}

// Обновленный метод collideBalls с проверкой isCollidable и сохранением точек
void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Point>* collisionPoints) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            
            // ПУНКТ 3: Если хотя бы один шар "призрачный", пропускаем коллизию
            if (!a->getIsCollidable() || !b->getIsCollidable()) {
                continue;
            }

            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2);
                
                // ПУНКТ 4: Сохраняем точку столкновения, если нам ее передали
                if (collisionPoints) {
                    Point midPoint = (a->getCenter() + b->getCenter()) / 2.0;
                    collisionPoints->push_back(midPoint);
                }
            }
        }
    }
}

// Обновленный метод collideWithBox с проверкой isCollidable
void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        
        // ПУНКТ 3: "Призрачные" шары пролетают и сквозь стены
        if (!ball.getIsCollidable()) {
            continue;
        }

        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));
}