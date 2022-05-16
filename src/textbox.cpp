#include "textbox.h"
#include "graphics.h"

#include <SDL2/SDL.h>

TextBox::TextBox () {

}

TextBox::TextBox(Graphics* _graphics, std::string path, int size) {
    graphics = _graphics;
    font = TTF_OpenFont(path.c_str(), size);
}

TextBox::TextBox(Graphics* _graphics, TTF_Font* _font) :
    graphics(_graphics),
    font(_font)
{}

TextBox::~TextBox () {
    TTF_CloseFont(font);
}

void TextBox::update(std::string text) {
    SDL_Surface* tmp = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, 1720);
    output = SDL_CreateTextureFromSurface(graphics->getRenderer(), tmp);
    //SDL_FreeSurface(tmp); // ??????

    // how tf does this even works until now ?????
    textureW = tmp->w;
    textureH = tmp->h;

    SDL_FreeSurface(tmp);
}

void TextBox::setSize(int _ptsize) {
    TTF_SetFontSize(font, _ptsize);
}

void TextBox::setColor(const SDL_Color& _color) {
    color = _color;
}

void TextBox::setPosition(const Vector2 &_position) {
    position = _position;
}

void TextBox::draw() {
    SDL_Rect src{0, 0, textureW, textureH};
    SDL_Rect dest{position.x, position.y, textureW, textureH};
    graphics->draw(output, &src, &dest);
    SDL_DestroyTexture(output);
}
