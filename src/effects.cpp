#include "effects.h"

Effects::Effects(Graphics* _graphics) :
    graphics {_graphics}
{}

Effects::~Effects() {}

void Effects::spawn(TextureData* data, const Vector2* _position) {
    Sprite* tmp = new Sprite(graphics, data, *_position);
    tmp->offsetPosition();
    tmp->looping(false);
    fxList.push_back(tmp);
}

void Effects::update() {
    for (size_t i = 0; i < fxList.size(); i++) {
        if (fxList[i]->draw() == false) {
            delete fxList[i];
            fxList.erase(fxList.begin()+i);
        }
    }
}
