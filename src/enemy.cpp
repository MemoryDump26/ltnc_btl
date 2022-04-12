#include "enemy.h"
#include "graphics.h"
#include "sprite.h"
#include "utils.h"
#include "globals.h"

namespace {
    const char ENEMY_SPRITE[] = "assets/sprites/enemy.png";
    const int SPRITE_WIDTH = 200;
    const int SPRITE_HEIGHT = 200;
    const double SPRITE_SCALE = 0.5;
}

Enemy::Enemy(Graphics* _graphics) :
    Sprite(_graphics, ENEMY_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE)
{
    addAnimation("idle", 0, 9, 5);
    hitbox = new SDL_Rect {0, 0, 100, 100};
}

Enemy::~Enemy() {

}

void Enemy::update() {
    position.x += rand() % 40;
    position.y += rand() % 40;
    position.x -= rand() % 40;
    position.y -= rand() % 40;
    position.x = clamp(position.x, 0, globals::GAME_WIDTH - SPRITE_WIDTH);
    position.y = clamp(position.y, 0, globals::GAME_HEIGHT - SPRITE_HEIGHT);

    hitbox->x = position.x;
    hitbox->y = position.y;
}
