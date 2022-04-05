#ifndef GAME_H
#define GAME_H

class SDL_Rect;

class Game {
public:
    Game();
    ~Game();
    void gameLoop();
    bool colliding(SDL_Rect* one, SDL_Rect* two);
private:

};

#endif
