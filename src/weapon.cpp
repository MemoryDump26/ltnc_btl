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

Weapon::Weapon(Graphics* _graphics, TextureData* data, const Vector2& _spawn) :
    Sprite(_graphics, data, _spawn)
{
    hitbox.r = d->width * d->scale / 2 * HITBOX_SCALE;
    hitbox.update(center);
}
Weapon::~Weapon() {

}

void Weapon::update(const Vector2* player) {

    switch (state) {
        case FIRED:
            position += angle / PROJECTILE_VELOCITY;
            if (cooldown.getTime() > WEAPON_COOLDOWN) {
                setAnimation("-1");
                cooldown.stop();
                state = COOLDOWN;
            }
            break;

        case COOLDOWN:
            int cursorX, cursorY;
            SDL_GetMouseState(&cursorX, &cursorY);
            cursor.x = cursorX;
            cursor.y = cursorY;
            cursor -= *player;

            double relDist = sqrt(pow(cursor.x, 2) + pow(cursor.y, 2));

            double scale = relDist / WEAPON_DISTANCE;
            angle = cursor / scale;

            position = *player + angle;
            position -= offset;

            break;
    }
    center = position + offset;
    hitbox.update(center);
}

void Weapon::fire() {
    if (state == COOLDOWN && power == 2) {
        cooldown.start();
        power = -1;
        state = FIRED;
    }
}

int Weapon::getPower() {
    return power;
}

void Weapon::hit() {
    if (state == COOLDOWN) {
        power = clamp(power + 1, 0, 2);
        setAnimation(std::to_string(power));
    }
}

void Weapon::reset() {
    setAnimation("-1");
    power = -1;
    cooldown.stop();
    state = COOLDOWN;
}

Vector2* Weapon::getCenter() {
    return &center;
}
