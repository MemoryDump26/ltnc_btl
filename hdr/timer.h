#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

#include <string>

class Timer {
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    void pause();
    void resume();
    bool isPausing();
    Uint64 getTime();
    std::string getTimeHuman();
private:
    Uint64 startTime = 0;
    Uint64 pausedTime = 0;
    bool pausing;
};

#endif
