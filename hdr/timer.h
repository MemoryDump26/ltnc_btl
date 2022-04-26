#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

#include <string>

class Timer {
public:
    Timer();
    ~Timer();
    void start();
    void pause();
    void resume();
    bool isPausing();
    Uint64 getTime();
    std::string getTimeHuman();
private:
    Uint64 startTime;
    Uint64 pausedTime;
    bool pausing;
};

#endif
