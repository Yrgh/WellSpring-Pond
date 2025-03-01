#include <core/error.h>
#include <video/Window.h>

Window::Window(int w, int h, const std::string &name, uint64_t sdl_flags, Renderer *inp_renderer) :
    renderer(inp_renderer) {
  
  renderer->window = this;
  
  _window = SDL_CreateWindow(name.c_str(), w, h, sdl_flags);
  if (!_window) {
    reportFatalSDLError("initializing window");
  }
}

Window::Window() :
    _window(nullptr), renderer(nullptr) {}

Window::~Window() {
  if (!_window) return;
  _on_destroy.call(this);
  SDL_DestroyWindow(_window);

  if (renderer) delete renderer;
}

SDL_Window *Window::getSDLPtr() {
  return _window;
}

void Window::draw() {
  renderer->render(scene);
}