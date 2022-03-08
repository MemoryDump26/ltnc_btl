#include "inputs.h"
#include <SDL2/SDL.h>

Inputs::Inputs() {

}

Inputs::~Inputs() {

}

void Inputs::getInputs() {
    pressedKeys.clear();
    releasedKeys.clear();

    while (SDL_PollEvent(&event) == 1) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN) {
            pressedKeys[event.key.keysym.sym] = true;
            heldKeys[event.key.keysym.sym] = true;
        }
        else if (event.type == SDL_KEYUP) {
            releasedKeys[event.key.keysym.sym] = true;
            heldKeys[event.key.keysym.sym] = false;
        }
    }
}

bool Inputs::isKeyPressed(SDL_Keycode key) {
    return pressedKeys[key];
}

bool Inputs::isKeyReleased(SDL_Keycode key) {
    return releasedKeys[key];
}

bool Inputs::isKeyHeld(SDL_Keycode key) {
    return heldKeys[key];
}

bool Inputs::quitting() {
    return quit;
}
