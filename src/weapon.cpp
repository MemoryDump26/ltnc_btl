#include "weapon.h"
#include "graphics.h"

#include "utils.h"
#include "area2d.h"
#include "vector2d.h"

#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const double HITBOX_SCALE = 0.333;

    const int WEAPON_COOLDOWN = 500;
    const int WEAPON_DISTANCE = 300;
    const int PROJECTILE_VELOCITY = 2;
}

Weapon::Weapon(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.r = d->width * d->scale / 2 * HITBOX_SCALE;
    hitbox.update(center);
}
Weapon::~Weapon() {

}

void Weapon::update(const Vector2<int>* player) {

    if (cooldown.isPausing() == false && cooldown.getTime() < WEAPON_COOLDOWN) {

        position += angle / PROJECTILE_VELOCITY;
        center = position + offset;

    }
    else {
        cooldown.stop();
        if (power == -1) {
            setAnimation("-1");
        }

        SDL_GetMouseState(&cursor.x, &cursor.y);
        cursor -= *player;

        double relDist = sqrt(pow(cursor.x, 2) + pow(cursor.y, 2));

        double scale = relDist / WEAPON_DISTANCE;
        angle = cursor / scale;

        position = *player + angle;

        position -= offset;
        center = position + offset;
    }

    hitbox.update(center);
}

void Weapon::fire() {
    if (cooldown.isPausing() == true && power == 2) {
        cooldown.start();
        power = -1;
    }
}

int Weapon::getPower() {
    return power;
}

void Weapon::hit() {
    if (cooldown.isPausing() == true) {
        power = clamp(power + 1, 0, 2);
        setAnimation(std::to_string(power));
    }
}

Vector2<int>* Weapon::getCenter() {
    return &center;
}
