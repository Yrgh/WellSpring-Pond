#pragma once
#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    SDL_Window *window;
public:
    // Creates a window
    Window(int w, int h, int x, int y, const std::string &name, int graphics_type);
    ~Window();
};