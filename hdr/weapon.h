#ifndef WEAPON_H
#define WEAPON_H

#include "sprite.h"
#include "area2d.h"
#include "vector2d.h"
#include "timer.h"

class Weapon : public Sprite{
public:
    Weapon(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn);
    ~Weapon();
    void update(const Vector2<int>* player);
    void fire();
    void hit();
    int getPower();
    Vector2<int>* getCenter();
    Circle hitbox;
private:
    Vector2<int> angle;
    Vector2<int> cursor;
    Timer cooldown;
    int power = 0;
};

#endif
