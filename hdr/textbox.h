#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "graphics.h"
#include "vector2d.h"

#include <SDL2/SDL_ttf.h>

#include <string>

class TextBox {
public:
    TextBox();
    TextBox(Graphics* _graphics, std::string path, int size);
    ~TextBox();
    void update(std::string text, SDL_Color* color);
    void draw();

private:
    TTF_Font* font;
    int textureW;
    int textureH;
    Vector2<int> position;
    Graphics* graphics;
    SDL_Texture* output;
    SDL_Color* color;
};

#endif
