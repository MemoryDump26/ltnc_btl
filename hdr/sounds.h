#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL_mixer.h>
#include <string>

class Sounds {
public:
    Sounds();
    ~Sounds();
    Mix_Chunk* loadFx(std::string path);
    Mix_Music* loadMusic(std::string path);
    void play(Mix_Chunk* fx);
    void loop(Mix_Chunk* fx);
    void pause();
    void playMusic(Mix_Music* music);
    void pauseMusic();
    bool isChannelPlaying(int channel);

private:

};

#endif
