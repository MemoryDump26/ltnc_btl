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

void Sprite::offsetPosition() {
    position -= offset;
}

void Sprite::setAnimation(std::string name) {
    if (currAnimation != name) {
        currAnimation = name;
        frameIndex = 0;
    }
}

void Sprite::looping(bool _looping) {
    loop = _looping;
}

bool Sprite::draw() {
    if (paused == true) return false;
    else {
        SDL_Rect destination = {position.x, position.y, scaledW, scaledH};

        graphics->draw(spritesheet, &animations[currAnimation][frameIndex], &destination);

        if (cooldown == 0) {
            frameIndex = (frameIndex + 1);
            cooldown = speed[currAnimation];
        }
        else cooldown--;
        if (frameIndex >= numOfFrame[currAnimation]) {
            frameIndex = 0;
            if (loop == false) {
                pause();
                return false;
            }
        }
        return true;
    }
}

void Sprite::pause() {
    paused = true;
}

void Sprite::resume() {
    paused = false;
}

Sprite::~Sprite() {

}
