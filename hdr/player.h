#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"

class SDL_Texture;
class SDL_Rect;
class Graphics;
class Weapon;


class Player {
public:
    Player(Graphics* _graphics);
    ~Player();
    void update();
    void draw();
    void moveLeft();
    void moveRight();
    void jump();
    void fire();
    void decelerate();
private:
    bool onGround;
    bool moving;
    Graphics* graphics;
    SDL_Texture* sprite;
    SDL_Rect* spriteRect;
    SDL_Rect* position;
    Vector2<double> friction;
    Vector2<double> gravity;
    Vector2<double> velocity;
    Vector2<double> acceleration;
    Weapon* weapon;
};

#endif
