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
    Graphics* graphics;
    SDL_Texture* sprite;
    SDL_Rect* spriteRect;
    SDL_Rect* position;
    vector2d friction;
    vector2d velocity;
    vector2d acceleration;
};

#endif
