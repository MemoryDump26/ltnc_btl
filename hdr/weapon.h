#ifndef WEAPON_H
#define WEAPON_H

#include "vector2d.h"
#include "sprite.h"

class Graphics;
class SDL_Rect;

class Weapon : public Sprite{
public:
    Weapon(Graphics* _graphics);
    ~Weapon();
    void update(const Vector2<int> player);
    void fire();
    SDL_Rect* hitbox;
private:
    Vector2<int> angle;
    Vector2<int> cursor;
    int cooldown = 0;
};

#endif
