#include "sprite.h"
#include "graphics.h"
#include "vector2d.h"
#include <SDL2/SDL.h>
#include <iostream>

Sprite::Sprite() {

}

Sprite::Sprite(
        Graphics* _graphics, const char path[], int _frameW, int _frameH,
        double scaler, const Vector2<int>& _spawn
        ) :
    offset{
        static_cast<int>(_frameW * scaler / 2),
        static_cast<int>(_frameH* scaler / 2)
    },
    graphics {_graphics},
    frameW  {_frameW},
    frameH {_frameH},
    position {_spawn}
{
    spritesheet = graphics->loadTexture(path);
    scaledW = frameW * scaler;
    scaledH = frameH * scaler;
    frameIndex = 0;
}

void Sprite::addAnimation(std::string animation, size_t start, size_t end, size_t _speed) {
    numOfFrame[animation] = end - start + 1;
    speed[animation] = _speed;
    cooldown = _speed;
    for (size_t i = start; i <= end; i++) {
        int col = i % 10;
        int row = i / 10;
        SDL_Rect frame = {frameW * col, frameH * row, frameW, frameH};
        animations[animation].push_back(frame);
    }
    if (currAnimation == "") currAnimation = animation;
}

void Sprite::setAnimation(std::string name) {
    if (currAnimation != name) {
        currAnimation = name;
        frameIndex = 0;
    }
}

void Sprite::draw() {

    SDL_Rect destination = {position.x, position.y, scaledW, scaledH};

    graphics->draw(spritesheet, &animations[currAnimation][frameIndex], &destination);

    if (cooldown == 0) {
        frameIndex = (frameIndex + 1) % numOfFrame[currAnimation];
        cooldown = speed[currAnimation];
    }
    else cooldown--;
}

Sprite::~Sprite() {

}


