#pragma once
#include <istream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    friend std::istream& operator>>(std::istream& is, Color& c) {
        return is >> c.r >> c.g >> c.b;
    }

  private:
    double r{};
    double g{};
    double b{};
};
