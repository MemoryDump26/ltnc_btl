#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "area2d.h"

class Enemy : public Sprite {
public:
    Enemy(Graphics* _graphics);
    ~Enemy();
    void update(const Vector2<int>& player);
    Circle hitbox;
private:
    Vector2<double> friction;
    Vector2<double> velocity;
    Vector2<double> acceleration;
};

#endif
