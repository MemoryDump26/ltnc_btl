#include "player.h"
#include "graphics.h"
#include "globals.h"
#include "vector2d.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

namespace {
    const char PLAYER_SPRITE[] = "assets/sprites/character.png";
    const double GRAVITY_CONST = 2;
    const double TERMINAL_VELOCITY = 10;
    const double ACCELERATION_CONST = 3;
    const double FRICTION_CONST = (ACCELERATION_CONST / TERMINAL_VELOCITY);
    const double JUMP_FORCE = -8;
}

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

Player::Player(Graphics* _graphics) {
    spriteRect = new SDL_Rect {0, 0, 250, 500};
    position = new SDL_Rect {0, 0, 25, 50};
    graphics = _graphics;
    sprite = graphics->loadTexture(PLAYER_SPRITE);
}

Player::~Player() {
}

void Player::update() {
    // Check if standing
    if (position->y == globals::GAME_HEIGHT - 50) onGround = true;
    else onGround = false;

    if (onGround) velocity.y = 0;

    // Apply gravity
    if (!onGround) acceleration.y += GRAVITY_CONST;

    // Apply friction
    friction.x = -velocity.x * FRICTION_CONST;
    acceleration = acceleration + friction;
    velocity += acceleration;
    //velocity.x = clamp(velocity.x, -TERMINAL_VELOCITY, TERMINAL_VELOCITY);
    velocity.y = std::min(velocity.y, TERMINAL_VELOCITY);

    position->x = clamp(round(position->x + velocity.x), 0.0, globals::GAME_WIDTH - 25.0);
    position->y = clamp((position->y + velocity.y), 0.0, globals::GAME_HEIGHT - 50.0);

    SDL_RenderCopy(graphics->getRenderer(), sprite, spriteRect, position);
    std::cout << "Velocity ";
    std::cout << std::fixed << std::setprecision(6)<< velocity.x << ' ' << velocity.y;
    std::cout << std::endl;
    std::cout << "Accel ";
    std::cout << std::fixed << std::setprecision(6)<< acceleration.x << ' ' << acceleration.y;
    std::cout << std::endl;
    std::cout << "Grounded " << std::boolalpha << onGround;
    std::cout << std::endl;
    //std::cout << std::fixed << std::setprecision(6)<< position->x << ' ' << position->y;
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
    //velocity.x = velocity.x / 3;
    //velocity.x = 0;
}

