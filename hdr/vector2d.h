#ifndef VECTOR2D_H
#define VECTOR2D_H

template <class T> class Vector2;
template <class T> Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2);
template <class T> Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2);
template <class T> Vector2<T> operator*(const Vector2<T>& v1, const double& v2);
template <class T> Vector2<T> operator/(const Vector2<T>& v1, const double& v2);

template <class T>
class Vector2 {
public:

    T x;
    T y;
    Vector2();
    Vector2(T _x, T _y);
    ~Vector2();

    friend Vector2<T> operator+ <> (const Vector2<T>& v1, const Vector2<T>& v2);
    Vector2<T>& operator+=(const Vector2<T>& rhs);

    friend Vector2<T> operator- <> (const Vector2<T>& v1, const Vector2<T>& v2);
    Vector2<T>& operator-=(const Vector2<T>& rhs);

    friend Vector2<T> operator* <> (const Vector2<T>& v1, const double& v2);
    Vector2<T>& operator*=(const double& rhs);

    friend Vector2<T> operator/ <> (const Vector2<T>& v1, const double& v2);
    Vector2<T>& operator/=(const double& rhs);
};

template <class T>
Vector2<T>::Vector2() {
    x = 0;
    y = 0;
}

template <class T>
Vector2<T>::Vector2(T _x, T _y) {
    x = _x;
    y = _y;
}

template <class T>
Vector2<T>::~Vector2() {

}

template <class T>
Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

template <class T>
Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2) {
    return Vector2<T>(v1.x + v2.x, v1.y + v2.y);
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

template <class T>
Vector2<T> operator*(const Vector2<T>& v1, const double& scalar) {
    return Vector2<T>(v1.x * scalar, v1.y * scalar);
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(const double& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

template <class T>
Vector2<T> operator/(const Vector2<T>& v1, const double& scalar) {
    return Vector2<T>(v1.x / scalar, v1.y / scalar);
}

template <class T>
Vector2<T>& Vector2<T>::operator/=(const double& rhs) {
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}

#endif
