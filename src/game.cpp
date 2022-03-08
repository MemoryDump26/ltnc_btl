#include "game.h"
#include "globals.h"
#include "graphics.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    gameLoop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::gameLoop() {
    Graphics graphics;
    int x = 0;
    int y = 0;
    bool quit = false;
    SDL_Rect source = {0, 0, 250, 500};
    SDL_Rect destination = {x, y, 25, 50};
    SDL_Texture* player = graphics.loadTexture(globals::PLAYER_SPRITE);

    while (!quit) {
        SDL_RenderClear(graphics.getRenderer());
        SDL_RenderCopy(graphics.getRenderer(), player, &source, &destination);
        destination = {x, y, 25, 50};
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_w) y -= 3;
            else if (event.key.keysym.sym == SDLK_s) y += 3;
            else if (event.key.keysym.sym == SDLK_a) x -= 3;
            else if (event.key.keysym.sym == SDLK_d) x += 3;
        }

        graphics.draw();

    }

}
