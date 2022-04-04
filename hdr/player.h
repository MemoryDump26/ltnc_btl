#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"

class Sprite;
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
    Vector2<double> friction;
    Vector2<double> gravity;
    Vector2<double> velocity;
    Vector2<double> acceleration;
    Vector2<int> position;
    Weapon* weapon;
    Sprite* sprite;
};

#endif
