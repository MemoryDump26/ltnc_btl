#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Graphics {
public:
    Graphics();
    ~Graphics();
    void draw();
    SDL_Texture* loadTexture(const char[]);
    SDL_Renderer* getRenderer();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
