#include "enemy.h"
#include "graphics.h"
#include "utils.h"
#include "globals.h"
#include "vector2d.h"

namespace {
    const char ENEMY_SPRITE[] = "assets/sprites/enemy.png";
    const int SPRITE_WIDTH = 1000;
    const int SPRITE_HEIGHT = 1000;
    const double SPRITE_SCALE = 0.1;
    const double HITBOX_SCALE = 0.3;
    const double FRICTION_CONST = -0.1;
    const double KNOCKBACK_CONST = 0.5;
    const int X_BOT_BOUND = - SPRITE_WIDTH * SPRITE_SCALE * HITBOX_SCALE;
    const int X_TOP_BOUND = globals::GAME_WIDTH + X_BOT_BOUND;
    const int Y_BOT_BOUND = - SPRITE_HEIGHT * SPRITE_SCALE * HITBOX_SCALE;
    const int Y_TOP_BOUND = globals::GAME_HEIGHT + Y_BOT_BOUND;
}

Enemy::Enemy(Graphics* _graphics, const Vector2<int>& _spawn) :
    Sprite(_graphics, ENEMY_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, _spawn)
{
    addAnimation("idle", 0, 9, 5);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE * HITBOX_SCALE;
}

Enemy::~Enemy() {

}

void Enemy::update(const Vector2<int>* player) {
    acceleration.x = (player->x - center.x) * 0.005;
    acceleration.y = (player->y - center.y) * 0.005;
    friction = velocity * FRICTION_CONST;

    if (hitTimer != 0) {
        acceleration *= 0.01;
        friction *= 0.5;
        hitTimer--;
    }

    velocity += acceleration + friction;
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x >= X_TOP_BOUND ||
        position.x <= 0) {
        velocity.x *= -0.3;
    }
    if (position.y >= Y_TOP_BOUND ||
        position.y <= 0) {
        velocity.y *= -0.3;
    }

    position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp(round(position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);

    center = position + offset;

    hitbox.update(center);
}

void Enemy::hit(const Vector2<int>* pPos) {
    velocity.x = (position.x - pPos->x) * KNOCKBACK_CONST;
    velocity.y = (position.y - pPos->y) * KNOCKBACK_CONST;
    hitTimer = 50;
}

void Enemy::gotHit(const Vector2<int>* wPos, int damage) {
    if (damage == 4) died();
    else {
        velocity.x = (position.x - wPos->x) * KNOCKBACK_CONST;
        velocity.y = (position.y - wPos->y) * KNOCKBACK_CONST;
        hitTimer = 50;
    }
}

void Enemy::died() {
    //setAnimation("died");
}
