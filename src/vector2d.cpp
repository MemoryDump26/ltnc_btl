#include "vector2d.h"

Vector2::Vector2() :
    x(0),
    y(0)
{}

Vector2::Vector2(float _x, float _y) :
    x(_x),
    y(_y)
{}

Vector2::~Vector2() {}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
    return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 operator*(const Vector2& lhs, const float scalar) {
    return Vector2(lhs.x * scalar, lhs.y * scalar);
}

Vector2 operator/(const Vector2& lhs, const float scalar) {
    return Vector2(lhs.x / scalar, lhs.y / scalar);
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(const float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(const float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}
