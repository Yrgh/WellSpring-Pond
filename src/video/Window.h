#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <events.h>

class Window {
private:
    SDL_Window *window;

    bool _is_not_ready = true;
    
    friend class GPUInterface;
    Event<Window *> _on_destroy;
public:
    // Creates a window
    Window(int w, int h, const std::string &name, uint64_t flags);
    Window();
    ~Window();

    inline SDL_Window *getSDLPtr() {
        return window;
    }

    // Call this on a variable to make it elligible for destruction
    void ready();
};