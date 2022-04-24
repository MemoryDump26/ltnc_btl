#ifndef EFFECTS_H
#define EFFECTS_H

#include "vector2d.h"
#include "sprite.h"
#include <vector>
#include <SDL2/SDL.h>

class Effects {
public:
    Effects(Graphics* _graphics);
    ~Effects();
    void spawn(TextureData* data, const Vector2<int>* _position);
    void update();

private:
    Graphics* graphics;
    std::vector<Sprite*> fxList;

};

#endif
