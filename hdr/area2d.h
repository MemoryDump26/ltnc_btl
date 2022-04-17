#ifndef AREA2_H
#define AREA2_H

#include "vector2d.h"

class Rectangle {
public:
    Rectangle();
    Rectangle(int _x, int _y, int _w, int _h);
    ~Rectangle();
    void update(const Vector2<int>& position);
    int x;
    int y;
    int w;
    int h;
};

class Circle {
public:
    Circle();
    Circle(int _x, int _y, int _r);
    ~Circle();
    void update(const Vector2<int>& center);
    int x;
    int y;
    int r;
};

bool colliding(const Rectangle& rect1, const Rectangle& rect2);
bool colliding(const Circle& cir1, const Circle& cir2);
bool colliding(const Circle& cir, const Rectangle& rect);

#endif
