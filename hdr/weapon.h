#ifndef WEAPON_H
#define WEAPON_H

#include "vector2d.h"

class Graphics;
class SDL_Rect;
class SDL_Texture;
class SDL_Cursor;

class Weapon {

public:
    Weapon(Graphics* _graphics);
    ~Weapon();
    void update(const int playerX, const int playerY);
    void fire();
    void draw();
private:
    Graphics* graphics;
    SDL_Rect* spriteRect;
    SDL_Rect* position;
    SDL_Texture* sprite;
    Vector2 angle;
    int cooldown = 0;
};

#endif
