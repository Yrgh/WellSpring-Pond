#pragma once
#include <SDL3/SDL.h>
#include <string>

class Window {
private:
    SDL_Window *window;

    bool _is_not_ready = true;
public:
    // Creates a window
    Window(int w, int h, const std::string &name, int graphics_type);
    Window();
    ~Window();

    inline SDL_Window *getSDLPtr() {
        return window;
    }

    // Call this on a variable to make it elligible for destruction
    void ready();
};