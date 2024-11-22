#include "Window.h"

#include "error.h"

Window::Window(int w, int h, const std::string &name, int graphics_type) {
    window = SDL_CreateWindow(name.c_str(), w, h, graphics_type);
    if (!window) {
        reportFatalSDLError("initializing window");
    }
}

Window::Window() : window(nullptr) {

}

Window::~Window() {
    if (_is_not_ready) return;
    if (!window) return;
    SDL_DestroyWindow(window);
}

void Window::ready() {
    _is_not_ready = false;
}