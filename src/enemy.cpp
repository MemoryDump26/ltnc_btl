#include "enemy.h"
#include "graphics.h"
#include "utils.h"
#include "globals.h"
#include "vector2d.h"

namespace {
    const char ENEMY_SPRITE[] = "assets/sprites/enemy_debug.png";
    const int SPRITE_WIDTH = 200;
    const int SPRITE_HEIGHT = 200;
    const double SPRITE_SCALE = 0.5;
    const double X_FRICTION_CONST = 0.5;
    const double Y_FRICTION_CONST = 0.5;
}

Enemy::Enemy(Graphics* _graphics, const Vector2<int>& _spawn) :
    Sprite(_graphics, ENEMY_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, _spawn)
{
    addAnimation("idle", 0, 0, 5);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE / 2;
}

Enemy::~Enemy() {

}

void Enemy::update(const Vector2<int>* player) {
    if (hitTimer != 0) {
        acceleration = {0, 0};
        friction = {0, 0};
        hitTimer--;
    }
    else {
        acceleration.x = (player->x - center.x) * 0.02;
        acceleration.y = (player->y - center.y) * 0.02;
        friction.x = -velocity.x * X_FRICTION_CONST;
        friction.y = -velocity.y * Y_FRICTION_CONST;
    }


    velocity += acceleration + friction;
    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x >= globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE ||
        position.x <= 0) {
        velocity.x *= -1;
    }
    if (position.y >= globals::GAME_HEIGHT - SPRITE_WIDTH * SPRITE_SCALE ||
        position.y <= 0) {
        velocity.y *= -1;
    }
    printf("Enemy at (%d, %d)", position.x, position.y);

    /*position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp(round(position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);*/

    center = position + offset;

    hitbox.update(center);
}

void Enemy::hit(const Vector2<int>* wPos, int damage) {
    if (damage == 4) died();
    else {
        velocity.x = (position.x - wPos->x);
        velocity.y = (position.y - wPos->y);
        hitTimer = 30;
    }
}

void Enemy::died() {
    //setAnimation("died");
}
