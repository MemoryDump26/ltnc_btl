#include "player.h"
#include "graphics.h"
#include "globals.h"
#include "utils.h"
#include <SDL2/SDL.h>

namespace {
    const int SPRITE_WIDTH = 250;
    const int SPRITE_HEIGHT = 500;
    const double SPRITE_SCALE = 0.25;
    const double GRAVITY_CONST = 2;
    const double ACCELERATION_CONST = 3;
    const double X_FRICTION_CONST = 0.25;
    const double Y_FRICTION_CONST = 0.1;
    const double JUMP_FORCE = -50;
    const int MAX_HEALTH = 100;
}

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

Player::Player(Graphics* _graphics, SDL_Texture* _spritesheet, Vector2<int> _spawn) :
    Sprite(_graphics, _spritesheet, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, _spawn)
{
    /*addAnimation("idle", 0, 1, 10);
    addAnimation("run", 0, 9, 5);*/
    addAnimation("idle", 0, 0, 1);
    addAnimation("run", 0, 0, 1);
    health = MAX_HEALTH;
    //hitbox = new SDL_Rect {0, 0, 125, 250};
    hitbox.w = SPRITE_WIDTH * SPRITE_SCALE;
    hitbox.h = SPRITE_HEIGHT * SPRITE_SCALE;
    iframe = 0;
}

Player::~Player() {
}

void Player::update() {

    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;
    velocity += acceleration + friction;

    position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp(round(position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);

    hitbox.update(position);

    center = position + offset;

    if (position.y == globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE) onGround = true;
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
