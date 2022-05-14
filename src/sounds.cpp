#include "sounds.h"

Sounds::Sounds() {
}

Sounds::~Sounds() {
}

Mix_Chunk* Sounds::loadFx(std::string path) {
    return Mix_LoadWAV(path.c_str());
}

Mix_Music* Sounds::loadMusic(std::string path) {
    return Mix_LoadMUS(path.c_str());
}

void Sounds::play(Mix_Chunk* fx) {
    Mix_PlayChannel(0, fx, 0);
}

void Sounds::loop(Mix_Chunk* fx) {
    Mix_PlayChannel(0, fx, -1);
}

void Sounds::pause() {
    Mix_Pause(0);
}

void Sounds::playMusic(Mix_Music* music) {
    Mix_PlayMusic(music, -1);
}

void Sounds::pauseMusic() {
    if (Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
    }
}

bool Sounds::isChannelPlaying(int channel) {
    return Mix_Playing(channel);
}

