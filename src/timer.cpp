#include "timer.h"
#include <SDL2/SDL_timer.h>

Timer::Timer() {}

void Timer::start() {
    startTime = SDL_GetTicks64();
    pausedTime = 0;
    pausing = false;
}

void Timer::pause() {
    if (pausing == false) {
        pausedTime = SDL_GetTicks64() - startTime;
    }
}

void Timer::resume() {
    if (pausing == true) {
        startTime = SDL_GetTicks64() - pausedTime;
        pausedTime = 0;
        pausing = false;
    }
}

Uint64 Timer::getTime() {
    return SDL_GetTicks64() - startTime;
}
