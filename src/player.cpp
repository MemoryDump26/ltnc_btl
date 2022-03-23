#include "player.h"
#include "weapon.h"
#include "graphics.h"
#include "globals.h"
#include "vector2d.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>

namespace {
    const char PLAYER_SPRITE[] = "assets/sprites/character.png";
    const double GRAVITY_CONST = 3;
    const double ACCELERATION_CONST = 3;
    const double X_FRICTION_CONST = 0.25;
    const double Y_FRICTION_CONST = 0.1;
    const double JUMP_FORCE = -50;
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
    weapon = new Weapon {graphics};
}

Player::~Player() {
}

void Player::update() {

    // Calculating velocity
    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;
    velocity += acceleration + friction;

    // Move the player
    position->x = clamp(round(position->x + velocity.x), 0.0, globals::GAME_WIDTH - 25.0);
    position->y = clamp((position->y + velocity.y), 0.0, globals::GAME_HEIGHT - 50.0);

    // Move the weapon
    weapon->update(position->x + 12, position->y + 25);

    // Check if the player is on the ground
    // to apply/clear gravity
    if (position->y == globals::GAME_HEIGHT - 50) onGround = true;
    else onGround = false;

    if (onGround) {
        velocity.y = 0;
        acceleration.y = 0;
    }
    else{
        acceleration.y = GRAVITY_CONST;
    }


    // Debug
    /*
    std::cout << "Velocity ";
    std::cout << std::fixed << std::setprecision(6)<< velocity.x << ' ' << velocity.y;
    std::cout << std::endl;
    std::cout << "Accel ";
    std::cout << std::fixed << std::setprecision(6)<< acceleration.x << ' ' << acceleration.y;
    std::cout << std::endl;
    std::cout << "Grounded " << std::boolalpha << onGround;
    std::cout << std::endl;
    */
}

void Player::draw() {
    SDL_RenderCopy(graphics->getRenderer(), sprite, spriteRect, position);
    weapon->draw();
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

void Player::fire() {
    weapon->fire();
}

void Player::decelerate() {
    acceleration.x = 0;
}

