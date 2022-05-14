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

Enemy::Enemy(Graphics* _graphics, TextureData* data, const Vector2& _spawn) :
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

void Enemy::update(const Vector2* player) {
    acceleration = (*player - center) * 0.005;
    friction = velocity * FRICTION_CONST;

    switch (state) {
        case SPAWN:
            acceleration *= 0.01;
            friction *= 0.5;
            looping(false);
            setAnimation("hit");
            if (isPausing()) {
                hitTimer.stop();
                state = ATTACK;
            }
            break;

        case ATTACK:
            looping(true);
            resume();
            setAnimation("idle");
            break;

        case HIT:
            acceleration *= 0.01;
            friction *= 0.5;
            looping(true);
            setAnimation("hit");
            if (hitTimer.getTime() > 1000) {
                hitTimer.stop();
                state = ATTACK;
            }
            break;

        case DIED:
            looping(false);
            setAnimation("died");
            if (isPausing()) isDead = true;
            break;

    }

    velocity += acceleration + friction;

    position += velocity;

    if (position.x >= xTopBound ||
        position.x <= xBotBound) {
        velocity.x *= -0.3;
    }
    if (position.y >= yTopBound ||
        position.y <= yBotBound) {
        velocity.y *= -0.3;
    }

    position.x = clamp(round(position.x), xBotBound, xTopBound);
    position.y = clamp(round(position.y), yBotBound, yTopBound);

    center = position + offset;

    hitbox.update(center);
}

void Enemy::hit(const Vector2* pPos) {
    if (state == ATTACK) {
        velocity = (center - *pPos) * KNOCKBACK_CONST;
        hitTimer.start();
        state = HIT;
    }
}

void Enemy::gotHit(const Vector2* wPos, int damage) {
    if (state != DIED) {
        velocity = (center - *wPos) * KNOCKBACK_CONST;
        if (damage == -1) {
            state = DIED;
        }
        else {
            hitTimer.start();
            state = HIT;
        }
    }
}

void Enemy::kill() {
    state = DIED;
}

Vector2* Enemy::getCenter() {
    return &center;
}
