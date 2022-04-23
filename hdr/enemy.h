#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "area2d.h"
#include "vector2d.h"

class Enemy : public Sprite {
public:
    Enemy(Graphics* _graphics, const Vector2<int>& _spawn);
    ~Enemy();
    void update(const Vector2<int>* player);
    void hit(const Vector2<int>* pPos);
    void gotHit(const Vector2<int>* wPos, int damage);
    void died();
    Vector2<int>* getCenter();
    Circle hitbox;
private:
    Vector2<double> friction;
    Vector2<double> velocity;
    Vector2<double> acceleration;
    int hitTimer = 0;
};

#endif
