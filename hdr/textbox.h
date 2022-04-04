#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "vector2d.h"
#include <SDL2/SDL_ttf.h>

class Graphics;

class TextBox {
public:
    TextBox();
    TextBox(Graphics* _graphics, const char* path, int size);
    ~TextBox();
    void update(const char* text, SDL_Color* color);
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
