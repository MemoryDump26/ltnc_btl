#ifndef ENEMY_H
#define ENEMY_H

#include "sprite.h"
#include "area2d.h"
#include "vector2d.h"
#include "timer.h"

enum EnemyState {
    SPAWN,
    ATTACK,
    HIT,
    DIED,
};

class Enemy : public Sprite {
public:
    Enemy(Graphics* _graphics, TextureData* data, const Vector2& _spawn);
    ~Enemy();
    void update(const Vector2* player);
    void hit(const Vector2* pPos);
    void gotHit(const Vector2* wPos, int damage);
    void kill();
    Vector2* getCenter();
    Circle hitbox;
    bool isDead = false;
    Timer hitTimer;
    EnemyState state = SPAWN;
private:
    Vector2 friction;
    Vector2 velocity;
    Vector2 acceleration;
};

#endif
