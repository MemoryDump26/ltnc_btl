#include "player.h"
#include "graphics.h"
#include "globals.h"
#include "vector2d.h"
#include <SDL2/SDL.h>

Player::Player(Graphics* _graphics) {
    spriteRect = new SDL_Rect {0, 0, 250, 500};
    position = new SDL_Rect {0, 0, 25, 50};
    graphics = _graphics;
    sprite = graphics->loadTexture(globals::PLAYER_SPRITE);
}

Player::~Player() {
}

void Player::update() {
    velocity.x = velocity.x + acceleration.x;
    velocity.y = velocity.y + acceleration.y;
    position->x += velocity.x;
    position->y += velocity.y;

    SDL_RenderCopy(graphics->getRenderer(), sprite, spriteRect, position);
}

void Player::moveLeft() {
    acceleration.x = -globals::ACCELERATION_CONST;
}

void Player::moveRight() {
    acceleration.x = globals::ACCELERATION_CONST;
}

void Player::jump() {
}

void Player::decelerate() {
    acceleration.x = 0;
    if (velocity.x != 0) velocity.x = 0;
}

