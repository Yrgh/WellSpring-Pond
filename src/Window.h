#pragma once
#include <SDL3/SDL.h>
#include <string>

class Window {
private:
    SDL_Window *window;
public:
    // Creates a window
    Window(int w, int h, const std::string &name, int graphics_type);
    ~Window();
};