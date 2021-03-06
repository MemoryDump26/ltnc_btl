#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vector2d.h"
#include <SDL2/SDL_ttf.h>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class Graphics {
public:
    Graphics();
    ~Graphics();
    void present();
    void draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest);
    void drawLine(Vector2* src, Vector2* dest);
    SDL_Texture* loadTexture(std::string path);
    SDL_Renderer* getRenderer();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
