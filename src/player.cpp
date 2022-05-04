#include "player.h"
#include "globals.h"
#include "graphics.h"

#include "utils.h"
#include "area2d.h"
#include "vector2d.h"

#include <SDL2/SDL.h>

namespace {
    const double HITBOX_SCALE = 1;

    const double GRAVITY_CONST = 1.8;
    const double ACCELERATION_CONST = 4;
    const double X_FRICTION_CONST = 0.25;
    const double Y_FRICTION_CONST = 0.1;
    const double JUMP_FORCE = -60;

    const int MAX_HEALTH = 100;
}

Player::Player(Graphics* _graphics, TextureData* data, Vector2<int> _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.w = d->width * d->scale * HITBOX_SCALE;
    hitbox.h = d->height * d->scale * HITBOX_SCALE;

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

    position.x = clamp(round(position.x + velocity.x), xBotBound, xTopBound);
    position.y = clamp(round(position.y + velocity.y), yBotBound, yTopBound);

    hitbox.update(position);

    center = position + offset;

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
}

void Player::moveLeft() {
    acceleration.x = -ACCELERATION_CONST;
    setAnimation("run");
}

void Player::moveRight() {
    acceleration.x = ACCELERATION_CONST;
    setAnimation("run");
}

void Player::decelerate() {
    acceleration.x = 0;
    setAnimation("idle");
}

void Player::jump() {
    if (onGround) {
        acceleration.y = JUMP_FORCE;
    }
}

void Player::gotHit(int damage) {
    if (!iframe) {
        health -= damage;
        iframe = 20;
    }
}

int Player::getHealth() {
    return health;
}

Vector2<int>* Player::getCenter() {
    return &center;
}
