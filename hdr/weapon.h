#ifndef WEAPON_H
#define WEAPON_H

#include "vector2d.h"

class Graphics;
class Sprite;

class Weapon {

public:
    Weapon(Graphics* _graphics);
    ~Weapon();
    void update(const Vector2<int> player);
    void fire();
    void draw();
private:
    Graphics* graphics;
    Vector2<int> angle;
    Vector2<int> cursor;
    Vector2<int> position;
    int cooldown = 0;
    Sprite* sprite;
};

#endif
