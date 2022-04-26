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
    Sprite(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn);
    ~Sprite();
    void addAnimation(std::string name, size_t start, size_t end, size_t _speed);
    void addAnimation();
    void offsetPosition();
    void setAnimation(std::string name);
    void looping(bool _looping);
    void pause();
    void resume();
    bool draw();
    bool drawOnce();

protected:
    TextureData* d;
    Vector2<int> position;
    Vector2<int> center;
    Vector2<int> offset;

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
