#include "textbox.h"
#include "graphics.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>


TextBox::TextBox () {

}

TextBox::TextBox(Graphics* _graphics, const char* path, int size) {
    graphics = _graphics;
    font = TTF_OpenFont(path, size);
}

TextBox::~TextBox () {
    TTF_CloseFont(font);
}

void TextBox::update(const char *text, SDL_Color* color) {
    SDL_Surface* tmp = TTF_RenderText_Blended(font, text, *color);
    output = SDL_CreateTextureFromSurface(graphics->getRenderer(), tmp);
    SDL_FreeSurface(tmp);

    textureW = tmp->w;
    textureH = tmp->h;
}

void TextBox::draw() {
    SDL_Rect* src = new SDL_Rect {0, 0, textureW, textureH};
    SDL_Rect* dest = new SDL_Rect {position.x, position.y, textureW, textureH};
    graphics->draw(output, src, dest);
}

