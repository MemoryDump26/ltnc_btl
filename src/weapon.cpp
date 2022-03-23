#include "weapon.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include <cmath>

namespace {
    const char WEAPON_SPRITE[] = "assets/sprites/weapon.png";
    const int WEAPON_DISTANCE = 200;
    const int PROJECTILE_VELOCITY = 2;
}

Weapon::Weapon(Graphics* _graphics) {
    spriteRect = new SDL_Rect {0, 0, 200, 200};
    position = new SDL_Rect {0, 0, 40, 40};
    graphics = _graphics;
    sprite = graphics->loadTexture(WEAPON_SPRITE);
}

Weapon::~Weapon() {

}

void Weapon::update(const int playerX, const int playerY) {

    if (cooldown == 0) {
        int cursorX, cursorY;
        SDL_GetMouseState(&cursorX, &cursorY);
        cursorX -= playerX;
        cursorY -= playerY;

        double relDist = sqrt(pow(cursorX, 2) + pow(cursorY, 2));

        double scale = relDist / WEAPON_DISTANCE;
        angle.x = cursorX / scale;
        angle.y = cursorY / scale;

        position->x = playerX + angle.x - 20;
        position->y = playerY + angle.y - 20;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(graphics->getRenderer(), playerX, playerY, position->x + 20, position->y + 20);
    }
    else {

        position->x += angle.x / PROJECTILE_VELOCITY;
        position->y += angle.y / PROJECTILE_VELOCITY;

        SDL_SetRenderDrawColor(graphics->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(graphics->getRenderer(), playerX, playerY, position->x + 20, position->y + 20);
        cooldown--;
    }
}

void Weapon::fire() {
    if (cooldown == 0) {
        cooldown = 50;
    }
}

void Weapon::draw() {
    SDL_RenderCopy(graphics->getRenderer(), sprite, spriteRect, position);
}
