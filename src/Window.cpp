#include "Window.h"

#include "error.cpp"

Window::Window(int w, int h, int x, int y, const std::string &name, int graphics_type) {
    window = SDL_CreateWindow(name.c_str(), x, y, w, h, SDL_WINDOW_SHOWN | graphics_type);
    if (!window) {
        reportFatalSDLError("initializing window");
    }
}
