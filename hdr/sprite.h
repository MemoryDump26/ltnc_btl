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
    Sprite(Graphics* _graphics, const char path[], int _frameW, int _frameH, double scaler);
    ~Sprite();
    void addAnimation(std::string name, size_t start, size_t end, size_t _speed);
    void setAnimation(std::string name);
    void draw();

protected:
    Vector2<int> position;
    Vector2<int> center;
    Graphics* graphics;

protected:
    size_t frameIndex;
    int cooldown;

private:
    int frameW;
    int frameH;
    int scaledW;
    int scaledH;
    //int speed;
    SDL_Texture* spritesheet;
    std::string currAnimation;
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, size_t> numOfFrame;
    std::map<std::string, size_t> speed;
};

#endif
