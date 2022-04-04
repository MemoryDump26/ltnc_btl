#include "weapon.h"
#include "graphics.h"
#include "sprite.h"
#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const char WEAPON_SPRITE[] = "assets/sprites/weapon.png";
    const int SPRITE_WIDTH = 200;
    const int SPRITE_HEIGHT = 200;
    const double SPRITE_SCALE = 0.5;
    const int WEAPON_DISTANCE = 200;
    const int PROJECTILE_VELOCITY = 2;
}

Weapon::Weapon(Graphics* _graphics) {
    graphics = _graphics;
    sprite = new Sprite {graphics, WEAPON_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, 1};
    sprite->addAnimation("idle", 0, 0);
}

Weapon::~Weapon() {

}

void Weapon::update(const Vector2<int> player) {

    if (cooldown == 0) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
        cursor -= player;

        double relDist = sqrt(pow(cursor.x, 2) + pow(cursor.y, 2));

        double scale = relDist / WEAPON_DISTANCE;
        angle = cursor / scale;

        position = player + angle;
        position -= {50, 50};

        SDL_SetRenderDrawColor(graphics->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(graphics->getRenderer(), player.x, player.y, position.x + 50, position.y + 50);
    }
    else {

        /*position->x += angle.x / PROJECTILE_VELOCITY;
        position->y += angle.y / PROJECTILE_VELOCITY;*/
        position += angle / PROJECTILE_VELOCITY;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(graphics->getRenderer(), player.x, player.y, position.x + 100, position.y + 100);
        //SDL_RenderDrawLine(graphics->getRenderer(), playerX, playerY, position->x + 20, position->y + 20);
        cooldown--;
    }
}

void Weapon::fire() {
    if (cooldown == 0) {
        cooldown = 50;
    }
}

void Weapon::draw() {
    sprite->play("idle", position);
}
