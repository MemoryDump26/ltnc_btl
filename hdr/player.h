#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"
#include "sprite.h"

class Graphics;
class Weapon;
class SDL_Rect;

class Player : public Sprite{
public:
    Player(Graphics* _graphics);
    ~Player();
    void update();
    void moveLeft();
    void moveRight();
    void jump();
    void fire();
    void decelerate();
    void hit(int damage);
    int getHealth();
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
    Vector2<int> center;
};

#endif
