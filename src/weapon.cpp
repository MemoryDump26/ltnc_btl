#include "weapon.h"
#include "graphics.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const char WEAPON_SPRITE[] = "assets/sprites/weapon.png";
    const int SPRITE_WIDTH = 500;
    const int SPRITE_HEIGHT = 500;
    const double SPRITE_SCALE = 0.25;
    const int WEAPON_DISTANCE = 200;
    const int PROJECTILE_VELOCITY = 3;
}

Weapon::Weapon(Graphics* _graphics, const Vector2<int>& _spawn) :
    Sprite(_graphics, WEAPON_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, _spawn)
{
    addAnimation("idle", 0, 9, 2);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE * 0.5;
}

Weapon::~Weapon() {

}

void Weapon::update(const Vector2<int>* player) {

    if (cooldown == 0) {
        SDL_GetMouseState(&cursor.x, &cursor.y);
        cursor -= *player;

        double relDist = sqrt(pow(cursor.x, 2) + pow(cursor.y, 2));

        double scale = relDist / WEAPON_DISTANCE;
        angle = cursor / scale;

        position = *player + angle;

        position -= offset;
        center = position + offset;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
        graphics->drawLine(*player, center);
    }
    else {

        position += angle / PROJECTILE_VELOCITY;
        center = position + offset;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
        graphics->drawLine(*player, center);
        cooldown--;
    }

    hitbox.update(center);
}

void Weapon::fire() {
    if (cooldown == 0 && power == 2) {
        cooldown = 50;
        power = -1;
    }
}

int Weapon::getPower() {
    return power;
}

void Weapon::hit() {
    if (cooldown == 0) {
        power = clamp(power + 1, 0, 2);
    }
}

Vector2<int>* Weapon::getCenter() {
    return &center;
}
