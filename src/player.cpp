#include "player.h"
#include "graphics.h"
#include "globals.h"
#include "vector2d.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <cmath>

Player::Player(Graphics* _graphics) {
    spriteRect = new SDL_Rect {0, 0, 250, 500};
    position = new SDL_Rect {0, 0, 25, 50};
    graphics = _graphics;
    sprite = graphics->loadTexture(globals::PLAYER_SPRITE);

}

Player::~Player() {
}

void Player::update() {
    if (!onGround) acceleration.y += globals::GRAVITY_CONST;
    else {
        velocity.y = 0;
        acceleration.y = 0;
    }
    velocity.x = clamp(
        velocity.x + acceleration.x,
        -globals::TERMINAL_VELOCITY,
        globals::TERMINAL_VELOCITY
        );
    velocity.y = clamp(
        velocity.y + acceleration.y,
        -globals::TERMINAL_VELOCITY,
        globals::TERMINAL_VELOCITY
        );

    position->x = clamp(position->x + velocity.x, 0, globals::GAME_WIDTH - 25);
    position->y = clamp(position->y + velocity.y, 0, globals::GAME_HEIGHT - 50);
    if (position->y == globals::GAME_HEIGHT - 50) onGround = true;

    SDL_RenderCopy(graphics->getRenderer(), sprite, spriteRect, position);
}

void Player::moveLeft() {
    acceleration.x = -globals::ACCELERATION_CONST;
}

void Player::moveRight() {
    acceleration.x = globals::ACCELERATION_CONST;
}

void Player::jump() {
    if (onGround) {
        acceleration.y += globals::JUMP_FORCE;
        onGround = false;
    }
}

void Player::decelerate() {
    acceleration.x = 0;
    velocity.x = velocity.x / 3;
}

