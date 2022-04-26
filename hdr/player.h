#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "area2d.h"
#include "vector2d.h"

class Player : public Sprite{
public:
    Player(Graphics* _graphics, TextureData* data, Vector2<int> _position);
    ~Player();
    void update();
    void moveLeft();
    void moveRight();
    void decelerate();
    void jump();
    void gotHit(int damage);
    int getHealth();
    Vector2<int>* getCenter();
    Rectangle hitbox;
private:
    int health;
    bool onGround;
    bool moving;
    int iframe;
    Vector2<double> friction;
    Vector2<double> velocity;
    Vector2<double> acceleration;
};

#endif
