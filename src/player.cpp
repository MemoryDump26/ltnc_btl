#include "player.h"
#include "weapon.h"
#include "graphics.h"
#include "globals.h"
#include "utils.h"
#include "sprite.h"
#include <SDL2/SDL.h>

namespace {
    const char PLAYER_SPRITE[] = "assets/sprites/character.png";
    const int SPRITE_WIDTH = 250;
    const int SPRITE_HEIGHT = 500;
    const double SPRITE_SCALE = 0.5;
    const int SPRITE_SPEED = 3;
    const double GRAVITY_CONST = 3;
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

Player::Player(Graphics* _graphics) :
    Sprite(_graphics, PLAYER_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, SPRITE_SPEED)
{
    addAnimation("run", 0, 9);
    health = MAX_HEALTH;
    hitbox = new SDL_Rect {0, 0, 125, 250};
}

Player::~Player() {
}

void Player::update() {

    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;
    velocity += acceleration + friction;

    position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp((position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);

    hitbox->x = position.x;
    hitbox->y = position.y;

    center.x = position.x + SPRITE_WIDTH * SPRITE_SCALE / 2;
    center.y = position.y + SPRITE_HEIGHT * SPRITE_SCALE / 2;

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
}

void Player::moveRight() {
        acceleration.x = ACCELERATION_CONST;
}

void Player::jump() {
    if (onGround) {
        acceleration.y = JUMP_FORCE;
    }
}

void Player::decelerate() {
    acceleration.x = 0;
}

void Player::hit(int damage) {
    if (!iframe) {
        health -= damage;
        iframe = 20;
    }
}

int Player::getHealth() {
    return health;
}

