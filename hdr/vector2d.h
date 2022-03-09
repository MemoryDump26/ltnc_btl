#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2 {
public:
    Vector2();
    Vector2(double _x, double _y);
    ~Vector2();

    friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
    Vector2& operator+=(const Vector2& rhs);

    friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
    Vector2& operator-=(const Vector2& rhs);

    friend Vector2 operator*(const Vector2& v1, const double& v2);
    Vector2& operator*=(const double& rhs);

    friend Vector2 operator/(const Vector2& v1, const double& v2);
    Vector2& operator/=(const double& rhs);

    double x;
    double y;

private:
};

#endif
