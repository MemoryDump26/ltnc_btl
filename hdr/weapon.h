#ifndef WEAPON_H
#define WEAPON_H

#include "sprite.h"
#include "area2d.h"
#include "vector2d.h"
#include "timer.h"

enum WeaponState {
    COOLDOWN,
    FIRED,
};

class Weapon : public Sprite{
public:
    Weapon(Graphics* _graphics, TextureData* data, const Vector2& _spawn);
    ~Weapon();
    void update(const Vector2* player);
    void fire();
    void hit();
    int getPower();
    Vector2* getCenter();
    Circle hitbox;
    WeaponState state = COOLDOWN;
private:
    Vector2 angle;
    Vector2 cursor;
    Timer cooldown;
    int power = 0;
};

#endif
