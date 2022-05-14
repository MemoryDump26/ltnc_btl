#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "sounds.h"
#include "inputs.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Game {
public:
    Game();
    ~Game();
    void loadData();
    void unloadData();
    void gameLoop();
private:
    Graphics graphics;
    Sounds sounds;
    Inputs inputs;
    std::map<std::string, SDL_Texture*> textures;
};

#endif
