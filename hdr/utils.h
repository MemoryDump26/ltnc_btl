#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

struct AnimationData {
    std::string name;
    int start;
    int end;
    int fps;
};

struct TextureData {
    std::string path;
    int width;
    int height;
    double scale;
    std::vector<AnimationData> animation;
    SDL_Texture* spritesheet = nullptr;
};

template<class T>
T clamp(const T value, const T low, const T high) {
    if (value < low) return low;
    else if (value > high) return high;
    else return value;
}


#endif
