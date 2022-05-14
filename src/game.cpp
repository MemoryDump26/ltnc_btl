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
#include <SDL2/SDL_mixer.h>

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
                0.3,
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
                0.5,
                {
                    {"default", 0, 1, 3},
                    {"idle", 0, 1, 3},
                    {"-1", 0, 1, 3},
                    {"0", 2, 3, 3},
                    {"1", 4, 5, 3},
                    {"2", 6, 29, 1},
                },
            },
        },
        {
            "enemy",
            {
                "assets/sprites/enemy.png",
                1000,
                1000,
                0.3,
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
                0.8,
                {
                    {"default", 0, 19, 1},
                },
            },
        },
    };
    std::map<std::string, soundData> sfxData {
                {
            "jump",
            {
                "assets/soundfx/jump.wav",
            },
        },
        {
            "fire",
            {
                "assets/soundfx/fire.wav",
            },
        },
    };
    std::map<std::string, musicData> musics {
        {
            "music",
            {
                "assets/music/1.wav",
            },
        },
    };
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    loadData();
    gameLoop();
}

Game::~Game() {
    Mix_CloseAudio();
    unloadData();
    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}

void Game::loadData() {
    for (auto& i : data) {
        i.second.spritesheet = graphics.loadTexture(i.second.path);
    }
    for (auto& i : sfxData) {
        i.second.audio = sounds.loadFx(i.second.path);
    }
    for (auto& i : musics) {
        i.second.audio = sounds.loadMusic(i.second.path);
    }
}

void Game::unloadData() {
    for (auto& i : data) {
        SDL_DestroyTexture(i.second.spritesheet);
        i.second.spritesheet = nullptr;
    }
    for (auto& i : sfxData) {
        Mix_FreeChunk(i.second.audio);
        i.second.audio = nullptr;
    }
    for (auto& i : musics) {
        Mix_FreeMusic(i.second.audio);
        i.second.audio = nullptr;
    }
}

void Game::gameLoop() {
    std::srand(std::time(0));

    Player player(&graphics, &data.at("player"), {0, 0});
    Weapon weapon(&graphics, &data.at("weapon"), {0, 0});
    EnemyManager spawn(&graphics, &data.at("enemy"));
    Effects effects(&graphics);
    TTF_Font* f_iosevka = TTF_OpenFont("assets/fonts/iosevka-regular.ttc", 60);
    TextBox text(&graphics, f_iosevka);
    SDL_Color color = {255, 255, 255, 255};
    Timer timePassed;
    timePassed.start();
    SDL_Texture* currBuffer = SDL_CreateTexture(graphics.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, globals::GAME_WIDTH, globals::GAME_HEIGHT);
    SDL_Texture* lastBuffer = SDL_CreateTexture(graphics.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, globals::GAME_WIDTH, globals::GAME_HEIGHT);
    SDL_SetTextureAlphaMod(lastBuffer, 230);
    SDL_SetTextureBlendMode(lastBuffer, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(currBuffer, SDL_BLENDMODE_BLEND);
    SDL_Rect* def = new SDL_Rect{0, 0, 1920, 1080};
    SDL_SetRenderDrawColor(graphics.getRenderer(), 0, 0, 0, 0);
    SDL_SetRenderDrawBlendMode(graphics.getRenderer(), SDL_BLENDMODE_BLEND);
    double delayTime = 16;

    sounds.playMusic(musics.at("music").audio);

    bool quit = false;
    while (!quit) {
        SDL_SetRenderTarget(graphics.getRenderer(), currBuffer);
        SDL_RenderClear(graphics.getRenderer());
        graphics.draw(lastBuffer, def, def);

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
            if (!sounds.isChannelPlaying(0)) {
                sounds.play(sfxData.at("jump").audio);
                }
        }

        if (inputs.isLeftClick()) {
            weapon.fire();
        }

        if (inputs.isKeyPressed(SDLK_p)) {
            sounds.pauseMusic();
        }

        if (inputs.isKeyPressed(SDLK_r)) {
            sounds.playMusic(musics.at("music").audio);
        }

        player.update();
        player.draw();
        weapon.update(player.getCenter());
        weapon.draw();

        spawn.update(player.getCenter());

        for (auto& i : spawn.enemies) {
            if (i->state != DIED) {
                if (colliding(i->hitbox, player.hitbox) && i->state == ATTACK) {
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

        if (weapon.getPower() == 2) {
            delayTime += (35 - delayTime) / 40;
            SDL_SetTextureAlphaMod(lastBuffer, 250);
        }
        else {
            delayTime -= (delayTime - 16) / 20;
            SDL_SetTextureAlphaMod(lastBuffer, 230);
        }

        effects.update();

        quit = inputs.quitting();

        color.r = rand() % 255;
        color.g = rand() % 255;
        color.b = rand() % 255;

        text.setColor(color);
        text.update(std::to_string(delayTime));
        text.draw();

        // This is gonna be fun lol
        SDL_SetRenderTarget(graphics.getRenderer(), NULL);
        SDL_RenderClear(graphics.getRenderer());
        graphics.draw(currBuffer, def, def);
        SDL_SetRenderTarget(graphics.getRenderer(), lastBuffer);
        SDL_RenderClear(graphics.getRenderer());
        graphics.draw(currBuffer, def, def);
        graphics.present();

        SDL_Delay(delayTime);
    }

}
