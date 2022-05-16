#ifndef SPRITE_H
#define SPRITE_H

#include "graphics.h"
#include "vector2d.h"
#include "utils.h"

#include <SDL2/SDL.h>

#include <map>
#include <vector>
#include <string>

class Sprite {
public:
    Sprite();
    Sprite(Graphics* _graphics, TextureData* data, const Vector2& _spawn);
    ~Sprite();
    void addAnimation();
    void offsetPosition();
    void setAnimation(std::string name);
    void looping(bool _looping);
    void pause();
    void resume();
    bool draw();
    bool isPausing();

protected:
    TextureData* d;
    Vector2 position;
    Vector2 offset;
    Vector2 center;
    float xTopBound;
    float yTopBound;
    float xBotBound;
    float yBotBound;

private:
    Graphics* graphics;
    int frameW;
    int frameH;
    int scaledW;
    int scaledH;
    int frameIndex = 0;
    int cooldown = 0;
    bool loop = true;
    bool paused = false;
    SDL_Texture* spritesheet;
    std::string currAnimation = "default";
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, int> numOfFrame;
    std::map<std::string, int> speed;
};

#endif
