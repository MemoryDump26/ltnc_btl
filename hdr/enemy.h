#ifndef ENEMY_H
#define ENEMY_H

#include "vector2d.h"
#include "sprite.h"

class Graphics;
class SDL_Rect;

class Enemy : public Sprite {
public:
    Enemy(Graphics* _graphics);
    ~Enemy();
    void update(const Vector2<int>& player);
    SDL_Rect* hitbox;
private:
    Vector2<double> friction;
    Vector2<double> velocity;
    Vector2<double> acceleration;
};

#endif
