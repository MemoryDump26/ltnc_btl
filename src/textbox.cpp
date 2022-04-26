#include "textbox.h"
#include "graphics.h"

#include <SDL2/SDL.h>

TextBox::TextBox () {

}

TextBox::TextBox(Graphics* _graphics, std::string path, int size) {
    graphics = _graphics;
    font = TTF_OpenFont(path.c_str(), size);
}

TextBox::~TextBox () {
    TTF_CloseFont(font);
}

void TextBox::update(std::string text, SDL_Color* color) {
    SDL_Surface* tmp = TTF_RenderText_Blended(font, text.c_str(), *color);
    output = SDL_CreateTextureFromSurface(graphics->getRenderer(), tmp);
    SDL_FreeSurface(tmp);

    textureW = tmp->w;
    textureH = tmp->h;
}

void TextBox::draw() {
    SDL_Rect* src = new SDL_Rect {0, 0, textureW, textureH};
    SDL_Rect* dest = new SDL_Rect {position.x, position.y, textureW, textureH};
    graphics->draw(output, src, dest);
    SDL_DestroyTexture(output);
}
