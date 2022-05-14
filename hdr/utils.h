#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <string>

struct AnimationData {
    const std::string name;
    const int start;
    const int end;
    const int fps;
};

struct TextureData {
    const std::string path;
    const int width;
    const int height;
    const double scale;
    const std::vector<AnimationData> animation;
    SDL_Texture* spritesheet = nullptr;
};

struct soundData {
    const std::string path;
    Mix_Chunk* audio = nullptr;
};

struct musicData {
    const std::string path;
    Mix_Music* audio = nullptr;
};

template<class T>
T clamp(const T value, const T low, const T high) {
    if (value < low) return low;
    else if (value > high) return high;
    else return value;
}

#endif
