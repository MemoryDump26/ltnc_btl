#include "game.h"
#include "globals.h"
#include "graphics.h"
#include "inputs.h"

#include "player.h"
#include "weapon.h"
#include "enemy.h"
#include "enemymanager.h"
#include "textbox.h"
#include "timer.h"
#include "effects.h"

#include "area2d.h"
#include "utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <ctime>
#include <iostream>
#include <map>
#include <string>

namespace {
    std::map<std::string, TextureData> data {
        {
            "player",
            {
                "assets/sprites/character_debug.png",
                250,
                500,
                0.25,
                {
                    {"default", 0, 0, 1},
                    {"idle", 0, 0, 1},
                    {"run", 0, 0, 1},
                },
            },
        },
        {
            "weapon",
            {
                "assets/sprites/weapon.png",
                1000,
                1000,
                0.4,
                {
                    {"default", 0, 9, 2},
                    {"idle", 0, 9, 2},
                },
            },
        },
        {
            "enemy",
            {
                "assets/sprites/enemy.png",
                1000,
                1000,
                0.2,
                {
                    {"default", 0, 9, 2},
                    {"idle", 0, 9, 2},
                    {"hit", 10, 11, 2},
                    {"died", 12, 24, 2},
                },
            },
        },
        {
            "hiteffect",
            {
                "assets/sprites/hiteffect.png",
                1000,
                1000,
                0.5,
                {
                    {"default", 0, 19, 1},
                },
            },
        },
    };
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    loadTexture();
    gameLoop();
}

Game::~Game() {
    unloadTexture();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::loadTexture() {
    for (auto& i : data) {
        i.second.spritesheet = graphics.loadTexture(i.second.path);
    }
}

void Game::unloadTexture() {
    for (auto& i : data) {
        SDL_DestroyTexture(i.second.spritesheet);
        i.second.spritesheet = nullptr;
    }
}

void Game::gameLoop() {
    std::srand(std::time(0));

    Player player(&graphics, &data.at("player"), {0, 0});
    Weapon weapon(&graphics, &data.at("weapon"), {0, 0});
    EnemyManager spawn(&graphics, &data.at("enemy"));
    Effects effects(&graphics);
    TextBox text(&graphics, "assets/fonts/iosevka-regular.ttc", 40);
    SDL_Color color = {255, 255, 255, 255};
    Timer timePassed;
    timePassed.start();

    bool quit = false;
    while (!quit) {
        Uint64 startTick = SDL_GetTicks64();
        SDL_RenderClear(graphics.getRenderer());

        inputs.getInputs();

        if (inputs.isKeyHeld(SDLK_d)) {
            player.moveRight();
        }
        else if (inputs.isKeyHeld(SDLK_a)) {
            player.moveLeft();
        }
        else {
            player.decelerate();
        }

        if (inputs.isKeyPressed(SDLK_SPACE)) {
            player.jump();
        }

        if (inputs.isLeftClick()) {
            weapon.fire();
        }

        player.update();
        player.draw();
        weapon.update(player.getCenter());
        weapon.draw();

        spawn.update(player.getCenter());

        for (auto& i : spawn.enemies) {
            if (i->isDead == false) {
                if (colliding(i->hitbox, player.hitbox)) {
                    i->hit(player.getCenter());
                    player.gotHit(20);
                }

                if (colliding(weapon.hitbox, i->hitbox)) {
                    weapon.hit();
                    i->gotHit(weapon.getCenter(), weapon.getPower());
                    effects.spawn(&data.at("hiteffect"), i->getCenter());
                }
            }
        }

        effects.update();

        quit = inputs.quitting();

        Uint64 endTick = SDL_GetTicks64();
        Uint64 elapsedTime = endTick - startTick;

        text.update(timePassed.getTimeHuman(), &color);
        text.draw();
        graphics.present();
        SDL_Delay((1000 / globals::GAME_FPS) - elapsedTime);
    }

}
