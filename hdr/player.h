#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"

class SDL_Texture;
class SDL_Rect;
class Graphics;


class Player {
public:
    Player(Graphics* _graphics);
    ~Player();
    void update();
    void moveLeft();
    void moveRight();
    void jump();
    void decelerate();
private:
    bool onGround;
    bool moving;
    Graphics* graphics;
    SDL_Texture* sprite;
    SDL_Rect* spriteRect;
    SDL_Rect* position;
    Vector2 friction;
    Vector2 gravity;
    Vector2 velocity;
    Vector2 acceleration;
};

#endif
