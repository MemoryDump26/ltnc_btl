#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2 {
public:
    float x;
    float y;
    Vector2();
    Vector2(float _x, float _y);
    ~Vector2();

    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator*(const Vector2& lhs, const float scalar);
    friend Vector2 operator/(const Vector2& lhs, const float scalar);

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator*=(const float scalar);
    Vector2& operator/=(const float scalar);
};

#endif
