#ifndef SPRITE_H
#define SPRITE_H

#include "vector2d.h"
#include <map>
#include <string>
#include <vector>

class Graphics;
class SDL_Texture;
class SDL_Rect;

class Sprite {
public:
    Sprite();
    Sprite(Graphics* _graphics, const char path[], int _frameW, int _frameH, double scaler, int _speed);
    ~Sprite();
    void addAnimation(std::string name, size_t start, size_t end);
    void setAnimation(std::string name);
    void draw();

protected:
    Vector2<int> position;
    Graphics* graphics;

private:
    int frameW;
    int frameH;
    int scaledW;
    int scaledH;
    int cooldown;
    int speed;
    size_t frameIndex;
    SDL_Texture* spritesheet;
    std::string currAnimation;
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, size_t> numOfFrame;
};

#endif
