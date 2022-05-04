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
    TextBox(Graphics* _graphics, TTF_Font* _font);
    ~TextBox();
    void update(std::string text);
    void setSize(int _ptsize);
    void setColor(const SDL_Color& _color);
    void setPosition(const Vector2<int>& _position);
    void draw();

private:
    Graphics* graphics;
    TTF_Font* font;
    int textureW;
    int textureH;
    Vector2<int> position;
    SDL_Texture* output;
    SDL_Color color;
};

#endif
