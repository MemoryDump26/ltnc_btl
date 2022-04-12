#include "game.h"
#include "globals.h"
#include "graphics.h"
#include "inputs.h"
#include "player.h"
#include "textbox.h"
#include "enemy.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <iostream>

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    gameLoop();
}

Game::~Game() {
    TTF_Quit();
    SDL_Quit();
}

void Game::gameLoop() {
    std::srand(std::time(0));
    Graphics graphics;
    Inputs inputs;
    Player player(&graphics);
    SDL_Color color = {0, 0, 0, 255};
    TextBox text(&graphics, "assets/fonts/iosevka-regular.ttc", 20);
    bool quit = false;
    Enemy test(&graphics);

    while (!quit) {
        Uint64 startTick = SDL_GetTicks64();
        SDL_RenderClear(graphics.getRenderer());

        inputs.getInputs();

        if (inputs.isKeyHeld(SDLK_d)) player.moveRight();
        else if (inputs.isKeyHeld(SDLK_a)) player.moveLeft();
        else player.decelerate();
        if (inputs.isKeyPressed(SDLK_SPACE)) player.jump();

        //if (inputs.isLeftClick()) player.fire();

        player.update();
        player.draw();
        test.update();
        test.draw();

        if (colliding(player.hitbox, test.hitbox)) {
            player.hit(20);
            std::cout << "hit! " << player.getHealth() << " HP left\n";
        }

        quit = inputs.quitting();

        SDL_SetRenderDrawColor(graphics.getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);

        Uint64 endTick = SDL_GetTicks64();
        Uint64 elapsedTime = endTick - startTick;

        char* elapsedText = new char[10];
        sprintf(elapsedText, "%d", player.getHealth());
        text.update(elapsedText, &color);
        text.draw();
        graphics.present();
        SDL_Delay((1000 / globals::GAME_FPS) - elapsedTime);
    }

}

bool Game::colliding(SDL_Rect* one, SDL_Rect* two) {
    if (one->x > two->x + two->w || one->x + one->w < two->x) return false;
    else if (one->y > two->y + two->h || one->y + one->h < two->y) return false;
    return true;
}
