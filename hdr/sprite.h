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
    void addAnimation(std::string animation, size_t start, size_t end);
    void play(std::string animation, const Vector2<int>& position);

private:
    Vector2<int> position;
    Graphics* graphics;
    int frameW;
    int frameH;
    int scaledW;
    int scaledH;
    int cooldown;
    int speed;
    size_t frameIndex;
    SDL_Texture* spritesheet;
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, size_t> numOfFrame;
};

#endif
