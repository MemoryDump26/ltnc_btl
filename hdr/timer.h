#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer {
public:
    Timer();
    ~Timer();
    void start();
    void pause();
    void resume();
    Uint64 getTime();
private:
    Uint64 startTime;
    Uint64 pausedTime;
    bool pausing;
};

#endif
