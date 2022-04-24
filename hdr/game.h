#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "inputs.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Game {
public:
    Game();
    ~Game();
    void loadTexture();
    void unloadTexture();
    void gameLoop();
private:
    Graphics graphics;
    Inputs inputs;
    std::map<std::string, SDL_Texture*> textures;
};

#endif
