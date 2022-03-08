#ifndef VECTOR2D_H
#define VECTOR2D_H

class vector2d {
public:
    vector2d();
    vector2d(int _x, int _y);
    ~vector2d();
    friend vector2d operator+(const vector2d v1, const vector2d v2);
    int x = 0;
    int y = 0;

private:
};

#endif
