#include "vector2d.h"

vector2d::vector2d() {
}

vector2d::vector2d(int _x, int _y) {
    x = _x;
    y = _y;
}

vector2d::~vector2d() {
}

vector2d operator+(const vector2d v1, const vector2d v2) {
    return vector2d(v1.x + v2.x, v1.y + v2.y);
}
