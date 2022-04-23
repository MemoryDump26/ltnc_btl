#include "weapon.h"
#include "graphics.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const char WEAPON_SPRITE[] = "assets/sprites/weapon.png";
    const int SPRITE_WIDTH = 1000;
    const int SPRITE_HEIGHT = 1000;
    const double SPRITE_SCALE = 0.2;
    const double HITBOX_SCALE = 0.333;
    const int WEAPON_DISTANCE = 200;
    const int PROJECTILE_VELOCITY = 3;
}

Weapon::Weapon(Graphics* _graphics, const Vector2<int>& _spawn) :
    Sprite(_graphics, WEAPON_SPRITE, SPRITE_WIDTH, SPRITE_HEIGHT, SPRITE_SCALE, _spawn)
{
    addAnimation("idle", 0, 9, 2);
    hitbox.r = SPRITE_WIDTH * SPRITE_SCALE / 2 * HITBOX_SCALE;
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
    }
    else {

        position += angle / PROJECTILE_VELOCITY;
        center = position + offset;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
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
