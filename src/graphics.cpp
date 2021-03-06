#include "graphics.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Graphics::Graphics() {
    window = SDL_CreateWindow(
            globals::GAME_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            globals::GAME_WIDTH,
            globals::GAME_HEIGHT,
            0
        );
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Graphics::~Graphics() {

}

SDL_Texture* Graphics::loadTexture(std::string path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Graphics::draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest)  {
    SDL_RenderCopy(renderer, texture, src, dest);
}

void Graphics::drawLine(Vector2* src, Vector2* dest) {
    SDL_RenderDrawLine(renderer, src->x, src->y, dest->x, dest->y);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Graphics::getRenderer() {
    return renderer;
}
