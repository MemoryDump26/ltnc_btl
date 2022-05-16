#include "player.h"
#include "globals.h"
#include "graphics.h"

#include "utils.h"
#include "area2d.h"
#include "vector2d.h"

#include <SDL2/SDL.h>

namespace {
    const double HITBOX_SCALE = 0.5;

    const double GRAVITY_CONST = 1.8;
    const double ACCELERATION_CONST = 4;
    const double X_FRICTION_CONST = 0.25;
    const double Y_FRICTION_CONST = 0.1;
    const double JUMP_FORCE = -60;

    const int MAX_HEALTH = 100;
}

Player::Player(Graphics* _graphics, TextureData* data, Vector2 _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.w = d->width * d->scale * HITBOX_SCALE;
    hitbox.h = d->height * d->scale * HITBOX_SCALE;
    hitbox.update(center);

    xBotBound = - d->width * d->scale * (1 - HITBOX_SCALE) / 2;
    xTopBound =
        globals::GAME_WIDTH - (d->width * d->scale) * (1 + HITBOX_SCALE) / 2;
    yBotBound = - d->height * d->scale * (1 - HITBOX_SCALE) / 2;
    yTopBound =
        globals::GAME_HEIGHT - (d->height * d->scale) * (1 + HITBOX_SCALE) / 2;

    health = MAX_HEALTH;
    iframe = 0;
}

Player::~Player() {
}

void Player::update() {
    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;

    velocity += acceleration + friction;
    position += velocity;

    position.x = clamp(position.x, xBotBound, xTopBound);
    position.y = clamp(position.y, yBotBound, yTopBound);

    hitbox.update(center);
    center = position + offset;

    switch (state) {
        case IDLE:
            looping(true);
            setAnimation("idle");
            break;
        case RUN:
            looping(false);
            setAnimation("run");
            break;
        case JUMP:
            looping(false);
            setAnimation("jump");
            if (position.y == yTopBound) {
                onGround = true;
                state = RUN;
            }
            else onGround = false;
            break;
        case DJUMP:
            looping(false);
            setAnimation("jump");
            if (position.y == yTopBound) {
                onGround = true;
                state = RUN;
            }
            else onGround = false;
            break;
    };

    if (position.y == yTopBound) onGround = true;
    else onGround = false;

    if (onGround) {
        velocity.y = 0;
        acceleration.y = 0;
    }
    else{
        acceleration.y = GRAVITY_CONST;
    }

    if (iframe) iframe--;
    printf("%d\n", state);
}

void Player::moveLeft() {
    acceleration.x = -ACCELERATION_CONST;
    if (state == IDLE) state = RUN;
}

void Player::moveRight() {
    acceleration.x = ACCELERATION_CONST;
    if (state == IDLE) state = RUN;
}

void Player::decelerate() {
    acceleration.x = 0;
    if (state == RUN) state = IDLE;
}

void Player::jump() {
    if (state == JUMP) {
        acceleration.y = JUMP_FORCE;
        resume();
        state = DJUMP;
    }
    else if (state != DJUMP) {
        acceleration.y = JUMP_FORCE;
        state = JUMP;
    }
}

void Player::gotHit(int damage) {
    if (!iframe) {
        health -= damage;
        iframe = 30;
    }
}

int Player::getHealth() {
    return health;
}

void Player::reset() {
    position = {0, 0};
    health = 100;
    state = DJUMP;
    iframe = 0;
}

Vector2* Player::getCenter() {
    return &center;
}
