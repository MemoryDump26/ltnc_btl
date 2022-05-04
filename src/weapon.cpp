#include "weapon.h"
#include "graphics.h"

#include "utils.h"
#include "area2d.h"
#include "vector2d.h"

#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const double HITBOX_SCALE = 0.333;

    const int WEAPON_DISTANCE = 300;
    const int PROJECTILE_VELOCITY = 2;
}

Weapon::Weapon(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.r = d->width * d->scale / 2 * HITBOX_SCALE;
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
    }
    else {

        position += angle / PROJECTILE_VELOCITY;
        center = position + offset;

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
