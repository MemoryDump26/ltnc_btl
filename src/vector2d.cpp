#include "vector2d.h"

Vector2::Vector2() {
    x = 0;
    y = 0;
}

Vector2::Vector2(double _x, double _y) {
    x = _x;
    y = _y;
}

Vector2::~Vector2() {
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x + v2.x, v1.y + v2.y);
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2 operator*(const Vector2& v1, const double& scalar) {
    return Vector2(v1.x * scalar, v1.y * scalar);
}

Vector2& Vector2::operator*=(const double& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}
Vector2 operator/(const Vector2& v1, const double& scalar) {
    return Vector2(v1.x / scalar, v1.y / scalar);
}

Vector2& Vector2::operator/=(const double& rhs) {
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}
