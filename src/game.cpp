#include "game.h"
#include "globals.h"
#include "graphics.h"
#include "inputs.h"
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
    Inputs inputs;
    int x = 0;
    int y = 0;
    bool quit = false;
    SDL_Rect source = {0, 0, 250, 500};
    SDL_Rect destination = {x, y, 25, 50};
    SDL_Texture* player = graphics.loadTexture(globals::PLAYER_SPRITE);

    while (!quit) {
        SDL_RenderClear(graphics.getRenderer());
        SDL_RenderCopy(graphics.getRenderer(), player, &source, &destination);

        inputs.getInputs();

        if (inputs.isKeyHeld(SDLK_w)) y -= 5;
        if (inputs.isKeyHeld(SDLK_s)) y += 5;
        if (inputs.isKeyHeld(SDLK_a)) x -= 5;
        if (inputs.isKeyHeld(SDLK_d)) x += 5;

        destination = {x, y, 25, 50};

        quit = inputs.quitting();

        /*SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.key.keysym.sym == SDLK_w) y -= 3;
            else if (event.key.keysym.sym == SDLK_s) y += 3;
            else if (event.key.keysym.sym == SDLK_a) x -= 3;
            else if (event.key.keysym.sym == SDLK_d) x += 3;
        }*/

        graphics.draw();
        SDL_Delay(16);
    }

}
