#include "area2d.h"
#include <algorithm>

Rectangle::Rectangle() {}

Rectangle::Rectangle(int _x, int _y, int _w, int _h) :
    x {_x},
    y {_y},
    w {_w},
    h {_h}
{}

Rectangle::~Rectangle() {}

void Rectangle::update(const Vector2<int>& position) {
    x = position.x;
    y = position.y;
}

Circle::Circle() {}

Circle::Circle(int _x, int _y, int _r) :
    x {_x},
    y {_y},
    r {_r}
{}

Circle::~Circle() {}

void Circle::update(const Vector2<int>& center) {
    x = center.x;
    y = center.y;
}

bool colliding(const Rectangle& rect1, const Rectangle& rect2) {
    if (rect1.x > rect2.x + rect2.w || rect1.x + rect1.w < rect2.x) return false;
    else if (rect1.y > rect2.y + rect2.h || rect1.y + rect1.h < rect2.y) return false;
    return true;
}

bool colliding(const Circle& cir1, const Circle& cir2) {
    int distSquare = (cir1.x - cir2.x) * (cir1.x - cir2.x) + (cir1.y - cir2.y) * (cir1.y - cir2.y);
    int radSquare = (cir1.r + cir2.r) * (cir1.r + cir2.r);

    if (distSquare <= radSquare) return true;
    else return false;
}

bool colliding(const Circle& cir, const Rectangle& rect) {
    int cx, cy;
    if (cir.x < rect.x) {
        cx = rect.x;
    }
    else if (cir.x > rect.x + rect.w) {
        cx = rect.x + rect.w;
    }
    else cx = cir.x;

    if (cir.y < rect.y) {
        cy = rect.y;
    }
    else if (cir.y > rect.y + rect.h) {
        cy = rect.y + rect.h;
    }
    else cy = cir.y;

    int distSquare = (cir.x - cx) * (cir.x - cx) + (cir.y - cy) * (cir.y - cy);
    int radSquare = cir.r * cir.r;

    if (distSquare <= radSquare) return true;
    else return false;
}
