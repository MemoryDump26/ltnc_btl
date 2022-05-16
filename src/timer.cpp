#include "timer.h"

#include <SDL2/SDL_timer.h>

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

Timer::Timer() {}
Timer::~Timer() {}

void Timer::start() {
    startTime = SDL_GetTicks64();
    pausedTime = 0;
    pausing = false;
}

void Timer::stop() {
    pausedTime = 0;
    pausing = true;
}

void Timer::pause() {
    if (pausing == false) {
        pausedTime = SDL_GetTicks64() - startTime;
        pausing = true;
    }
}

void Timer::resume() {
    if (pausing == true) {
        startTime = SDL_GetTicks64() - pausedTime;
        pausedTime = 0;
        pausing = false;
    }
}

bool Timer::isPausing() {
    return pausing;
}

Uint64 Timer::getTime() {
    if (pausing == true) {
        return pausedTime;
    }
    else return SDL_GetTicks64() - startTime;
}

std::string Timer::getTimeHuman() {
    int seconds = getTime() / 1000;
    int hours = seconds / 3600;
    int minutes = seconds % 3600 / 60;
    seconds = seconds % 60;
    std::stringstream tmp;
    tmp << std::setw(2) << std::setfill('0') << hours << ":";
    tmp << std::setw(2) << std::setfill('0') << minutes << ":";
    tmp << std::setw(2) << std::setfill('0') << seconds;
    return tmp.str();
}
