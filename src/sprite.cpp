#include "sprite.h"
#include "graphics.h"
#include "vector2d.h"
#include <SDL2/SDL.h>

Sprite::Sprite() {

}

Sprite::Sprite(Graphics* _graphics, const char path[], int _frameW, int _frameH, double scaler, int _speed) {
    graphics = _graphics;
    spritesheet = graphics->loadTexture(path);
    frameH = _frameH;
    frameW = _frameW;
    scaledW = frameW * scaler;
    scaledH = frameH * scaler;
    frameIndex = 0;
    speed = _speed;
    cooldown = speed;
}

void Sprite::addAnimation(std::string animation, size_t start, size_t end) {
    numOfFrame[animation] = end - start + 1;
    for (size_t i = start; i <= end; i++) {
        int col = i % 10;
        int row = i / 10;
        SDL_Rect frame = {frameW * col, frameH * row, frameW, frameH};
        animations[animation].push_back(frame);
    }
}

void Sprite::play(std::string animation, const Vector2<int>& position) {

    SDL_Rect destination = {position.x, position.y, scaledW, scaledH};
    /*SDL_RenderCopy(
            graphics->getRenderer(),
            spritesheet,
            &animations[animation][frameIndex],
            &destination
        );*/
    graphics->draw(spritesheet, &animations[animation][frameIndex], &destination);

    if (cooldown == 0) {
        frameIndex = (frameIndex + 1) % numOfFrame[animation];
        cooldown = speed;
    }
    else cooldown--;
}

Sprite::~Sprite() {

}


