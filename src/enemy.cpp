#include "enemy.h"
#include "globals.h"
#include "graphics.h"

#include "utils.h"
#include "area2d.h"
#include "vector2d.h"

namespace {
    const double HITBOX_SCALE = 0.333;
    const double FRICTION_CONST = -0.1;
    const double KNOCKBACK_CONST = 0.7;
}

Enemy::Enemy(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.r = d->width * d->scale / 2 * HITBOX_SCALE;
    hitbox.update(center);

    xBotBound = - d->width * d->scale * (1 - HITBOX_SCALE) / 2;
    xTopBound =
        globals::GAME_WIDTH - (d->width * d->scale) * (1 + HITBOX_SCALE) / 2;
    yBotBound = - d->height * d->scale * (1 - HITBOX_SCALE) / 2;
    yTopBound =
        globals::GAME_HEIGHT - (d->height * d->scale) * (1 + HITBOX_SCALE) / 2;

    hitTimer.start();
    setAnimation("hit");
}

Enemy::~Enemy() {

}

void Enemy::update(const Vector2<int>* player) {
    acceleration.x = (player->x - center.x) * 0.005;
    acceleration.y = (player->y - center.y) * 0.005;
    friction = velocity * FRICTION_CONST;

    if (hitTimer.isPausing() == false && hitTimer.getTime() < 1000) {
        acceleration *= 0.01;
        friction *= 0.5;
    }
    else {
        hitTimer.stop();
        looping(true);
        resume();
        setAnimation("idle");
    }

    velocity += acceleration + friction;

    position.x += velocity.x;
    position.y += velocity.y;

    if (position.x >= xTopBound ||
        position.x <= xBotBound) {
        velocity.x *= -0.3;
    }
    if (position.y >= yTopBound ||
        position.y <= yBotBound) {
        velocity.y *= -0.3;
    }

    position.x = clamp(round(position.x + velocity.x), xBotBound, xTopBound);
    position.y = clamp(round(position.y + velocity.y), yBotBound, yTopBound);

    center = position + offset;

    hitbox.update(center);
}

void Enemy::hit(const Vector2<int>* pPos) {
    if (hitTimer.isPausing() == true) {
        velocity.x = (center.x - pPos->x) * KNOCKBACK_CONST;
        velocity.y = (center.y - pPos->y) * KNOCKBACK_CONST;
        hitTimer.start();
    }
}

void Enemy::gotHit(const Vector2<int>* wPos, int damage) {
    velocity.x = (center.x - wPos->x) * KNOCKBACK_CONST;
    velocity.y = (center.y - wPos->y) * KNOCKBACK_CONST;
    if (damage == -1) {
        hitTimer.start();
        died();
    }
    else {
        hitTimer.start();
        setAnimation("hit");
    }
}

void Enemy::died() {
    looping(false);
    setAnimation("died");
    isDead = true;
}

Vector2<int>* Enemy::getCenter() {
    return &center;
}
