#include "player.h"
#include "weapon.h"
#include "graphics.h"
#include "globals.h"
#include "vector2d.h"
#include "utils.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <iomanip>

namespace {
    const char PLAYER_SPRITE[] = "assets/sprites/character.png";
    const int SPRITE_WIDTH = 250;
    const int SPRITE_HEIGHT = 500;
    const double SPRITE_SCALE = 0.5;
    const int TICK_PER_FRAME = 3;
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
    graphics = _graphics;
    weapon = new Weapon {graphics};
    sprite = new Sprite {graphics, PLAYER_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, TICK_PER_FRAME};
    sprite->addAnimation("run", 0, 9);
}

Player::~Player() {
}

void Player::update() {

    // Calculating velocity
    friction.x = -velocity.x * X_FRICTION_CONST;
    friction.y = -velocity.y * Y_FRICTION_CONST;
    velocity += acceleration + friction;

    // Move the player
    // round() because the character still move 1 pixel left
    // even if velocity is like -0.000069 or something :/
    position.x = clamp(round(position.x + velocity.x), 0.0, globals::GAME_WIDTH - SPRITE_WIDTH * SPRITE_SCALE);
    position.y = clamp((position.y + velocity.y), 0.0, globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE);

    // Move the weapon
    Vector2<int> center;
    center.x = position.x + SPRITE_WIDTH * SPRITE_SCALE / 2;
    center.y = position.y + SPRITE_HEIGHT * SPRITE_SCALE / 2;
    weapon->update(center);

    // Check if the player is on the ground
    // to apply/clear gravity
    if (position.y == globals::GAME_HEIGHT - SPRITE_HEIGHT * SPRITE_SCALE) onGround = true;
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
    sprite->play("run", position);
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

