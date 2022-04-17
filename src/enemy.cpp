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
    const double X_FRICTION_CONST = 0.4;
    const double Y_FRICTION_CONST = 0.4;
}

Enemy::Enemy(Graphics* _graphics) :
    Sprite(_graphics, ENEMY_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE)
{
    addAnimation("idle", 0, 0, 5);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE / 2;
}

Enemy::~Enemy() {

}

void Enemy::update(const Vector2<int>& player) {
    acceleration.x = (player.x - center.x) * 0.01;
    acceleration.y = (player.y - center.y) * 0.01;

    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;

    velocity += acceleration + friction;

    position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp(round(position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);

    center.x = position.x + SPRITE_WIDTH * SPRITE_SCALE / 2;
    center.y = position.y + SPRITE_HEIGHT * SPRITE_SCALE / 2;

    hitbox.update(center);
}
