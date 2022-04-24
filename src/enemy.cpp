#include "enemy.h"
#include "graphics.h"
#include "utils.h"
#include "globals.h"
#include "vector2d.h"

namespace {
    const int SPRITE_WIDTH = 1000;
    const int SPRITE_HEIGHT = 1000;
    const double SPRITE_SCALE = 0.2;
    const double HITBOX_SCALE = 0.333; // pIxEl pERfEcT lol
    const double FRICTION_CONST = -0.1;
    const double KNOCKBACK_CONST = 0.7;
    // ???? quick maff ???? //
    const int X_BOT_BOUND = - SPRITE_WIDTH * SPRITE_SCALE * (1 - HITBOX_SCALE) / 2;
    const int X_TOP_BOUND =
        globals::GAME_WIDTH - (SPRITE_WIDTH * SPRITE_SCALE) * (1 + HITBOX_SCALE) / 2;
    const int Y_BOT_BOUND = - SPRITE_HEIGHT * SPRITE_SCALE * (1 - HITBOX_SCALE) / 2;
    const int Y_TOP_BOUND =
        globals::GAME_HEIGHT - (SPRITE_HEIGHT * SPRITE_SCALE) * (1 + HITBOX_SCALE) / 2;
}

Enemy::Enemy(Graphics* _graphics, const TextureData& data, const Vector2<int>& _spawn) :
    Sprite(_graphics, data, _spawn)
{
    addAnimation("idle", 0, 9, 5);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE / 2 * HITBOX_SCALE;
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
        position.x <= X_BOT_BOUND) {
        velocity.x *= -0.3;
    }
    if (position.y >= Y_TOP_BOUND ||
        position.y <= Y_BOT_BOUND) {
        velocity.y *= -0.3;
    }

    position.x = clamp(round(position.x + velocity.x), (double)X_BOT_BOUND, (double)X_TOP_BOUND);
    position.y = clamp(round(position.y + velocity.y), (double)Y_BOT_BOUND, (double)Y_TOP_BOUND);
    center = position + offset;

    hitbox.update(center);
}

void Enemy::hit(const Vector2<int>* pPos) {
    if (hitTimer == 0) {
        velocity.x = (center.x - pPos->x) * KNOCKBACK_CONST;
        velocity.y = (center.y - pPos->y) * KNOCKBACK_CONST;
        hitTimer = 50;
    }
}

void Enemy::gotHit(const Vector2<int>* wPos, int damage) {
    velocity.x = (center.x - wPos->x) * KNOCKBACK_CONST;
    velocity.y = (center.y - wPos->y) * KNOCKBACK_CONST;
    if (damage == 4) {
        died();
    }
    else {
        hitTimer = 50;
    }
}

void Enemy::died() {
    //setAnimation("died");
}

Vector2<int>* Enemy::getCenter() {
    return &center;
}
