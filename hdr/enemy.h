#ifndef ENEMY_H
#define ENEMY_H

#include "vector2d.h"

class Sprite;
class Graphics;
class SDL_Rect;

class Enemy {
public:
    Enemy(Graphics* _graphics);
    ~Enemy();
    void update();
    void draw();
    SDL_Rect* hitbox;
private:
    Graphics* graphics;
    Sprite* sprite;
    Vector2<double> friction;
    Vector2<double> gravity;
    Vector2<double> velocity;
    Vector2<double> acceleration;
    Vector2<int> position;
    Vector2<int> center;
};

#endif
