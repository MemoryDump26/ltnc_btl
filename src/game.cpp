#include "game.h"
#include "globals.h"
#include "graphics.h"
#include "inputs.h"
#include "player.h"
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
    Player player(&graphics);
    bool quit = false;

    while (!quit) {
        SDL_RenderClear(graphics.getRenderer());

        inputs.getInputs();

        if (inputs.isKeyHeld(SDLK_d)) player.moveRight();
        else if (inputs.isKeyHeld(SDLK_a)) player.moveLeft();
        else player.decelerate();
        if (inputs.isKeyPressed(SDLK_SPACE)) player.jump();

        player.update();

        quit = inputs.quitting();

        graphics.present();
        SDL_Delay(16);
    }

}
