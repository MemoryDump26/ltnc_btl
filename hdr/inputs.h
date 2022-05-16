#ifndef INPUTS_H
#define INPUTS_H

#include <SDL2/SDL.h>

#include <map>

class Inputs {
public:
    Inputs();
    ~Inputs();
    void getInputs();
    bool isKeyPressed(SDL_Keycode);
    bool isKeyReleased(SDL_Keycode);
    bool isKeyHeld(SDL_Keycode);
    bool isLeftClick();
    bool quitting();
private:
    SDL_Event event;
    bool quit = false;
    std::map<SDL_Keycode, bool> pressedKeys;
    std::map<SDL_Keycode, bool> releasedKeys;
    std::map<SDL_Keycode, bool> heldKeys;
    bool leftClick;
};

#endif
