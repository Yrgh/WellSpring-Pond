#include "Window.h"

#include "error.cpp"

Window::Window(int w, int h, const std::string &name, int graphics_type) {
    window = SDL_CreateWindow(name.c_str(), w, h, graphics_type);
    if (!window) {
        reportFatalSDLError("initializing window");
    }
}
