#ifndef GRAPHICS_H
#define GRAPHICS_H

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
    SDL_Texture* loadTexture(const char[]);
    SDL_Renderer* getRenderer();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
