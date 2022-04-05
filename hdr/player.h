#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"

class Sprite;
class Graphics;
class Weapon;
class SDL_Rect;

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
    void hit(int damage);
    int getHealth();
    SDL_Rect* hitbox;
private:
    int health;
    bool onGround;
    bool moving;
    int iframe;
    Graphics* graphics;
    Vector2<double> friction;
    Vector2<double> gravity;
    Vector2<double> velocity;
    Vector2<double> acceleration;
    Vector2<int> position;
    Vector2<int> center;
    Weapon* weapon;
    Sprite* sprite;
};

#endif
