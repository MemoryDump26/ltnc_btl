#include "sprite.h"
#include "graphics.h"
#include "vector2d.h"
#include <SDL2/SDL.h>
#include <iostream>

Sprite::Sprite() {

}

Sprite::Sprite(Graphics* _graphics, TextureData* data, const Vector2<int>& _spawn) :
    d(data),
    position(_spawn),
    offset(
        static_cast<int>(data->width * data->scale / 2),
        static_cast<int>(data->height * data->scale / 2)
    ),
    graphics(_graphics),
    frameW(data->width),
    frameH(data->height),
    spritesheet(data->spritesheet)
{
    scaledW = data->width * data->scale;
    scaledH = data->height * data->scale;
    addAnimation();
}

void Sprite::addAnimation() {
    for (auto& i : d->animation) {
        numOfFrame[i.name] = i.end - i.start + 1;
        speed[i.name] = i.fps; // not really lmao;
        cooldown = i.fps;
        for (auto j = i.start; j <= i.end; j++) {
            int col = j % 10;
            int row = j / 10;
            SDL_Rect frame = {d->width * col, d->height * row, d->width, d->height};
            animations[i.name].push_back(frame);
        }
    }
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

void Sprite::offsetPosition() {
    position -= offset;
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

bool Sprite::drawOnce() {
    SDL_Rect destination = {position.x, position.y, scaledW, scaledH};

    graphics->draw(spritesheet, &animations[currAnimation][frameIndex], &destination);

    if (cooldown == 0) {
        frameIndex = (frameIndex + 1);
        cooldown = speed[currAnimation];
    }
    else cooldown--;
    if (frameIndex >= numOfFrame[currAnimation]) return false;
    else return true;
}


Sprite::~Sprite() {

}

