#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "sprite.h"

class Graphics;
class SDL_Rect;

class Player : public Sprite{
public:
    Player(Graphics* _graphics);
    ~Player();
    void update();
    void moveLeft();
    void moveRight();
    void decelerate();
    void jump();
    void hit(int damage);
    int getHealth();
    Vector2<int> getCenter();
    SDL_Rect* hitbox;
private:
    int health;
    bool onGround;
    bool moving;
    int iframe;
    Vector2<double> friction;
    Vector2<double> gravity;
    Vector2<double> velocity;
    Vector2<double> acceleration;
};

#endif
