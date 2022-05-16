#ifndef EFFECTS_H
#define EFFECTS_H

#include "sprite.h"
#include "vector2d.h"

#include <SDL2/SDL.h>

#include <vector>

class Effects {
public:
    Effects(Graphics* _graphics);
    ~Effects();
    void spawn(TextureData* data, const Vector2* _position);
    void update();

private:
    Graphics* graphics;
    std::vector<Sprite*> fxList;

};

#endif
