#include <video/Window.h>

Window::Window(int w, int h, uint64_t sdl_flags, Renderer *inp_renderer) :
    renderer(inp_renderer) {

  renderer->window = this;
  
  _window = SDL_CreateWindow("WSGLOBAL_APP_NAME", w, h, sdl_flags);
  if (!_window) {
    reportFatalSDLError("initializing window");
  }

  renderer->onWindowEncapsulation(*this);
}

Window::Window() : _window(nullptr), renderer(nullptr) {}

#include <iostream>
Window::~Window() {
  if (!_window) return;
  _on_destroy.call(this);
  SDL_DestroyWindow(_window);

  if (renderer) delete renderer;
}

bool Window::hasParent() const {
  if (!_window) { reportFatalError("Window does not exist"); }

  return _parent != nullptr;
}

Window &Window::getParent() {
  if (!_window) { reportFatalError("Window does not exist"); }

  return *_parent;
}

void Window::setParent(const Window &par) {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_SetWindowParent(_window, par._window);
}

void Window::deparent() {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_SetWindowParent(_window, nullptr);
}

SDL_Window *Window::getSDLPtr() {
  return _window;
}

Vec2i Window::getSize() const {
  if (!_window) { reportFatalError("Window does not exist"); }

  Vec2i result = {0, 0};
  SDL_GetWindowSizeInPixels(_window, &result.x, &result.y);
  return result;
}

void Window::setSize(const Vec2i &size) {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_SetWindowSize(_window, size.x, size.y);
}

Vec2i Window::getPosition() const {
  if (!_window) { reportFatalError("Window does not exist"); }

  Vec2i result = {0, 0};
  SDL_GetWindowPosition(_window, &result.x, &result.y);
  return result;
}

void Window::setPosition(const Vec2i &pos) {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_SetWindowPosition(_window, pos.x, pos.y);
}

void Window::flashUntilFocused() {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_FlashWindow(_window, SDL_FLASH_UNTIL_FOCUSED);
}

void Window::flashTemporarily() {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_FlashWindow(_window, SDL_FLASH_BRIEFLY);
}

void Window::focus() {
  if (!_window) { reportFatalError("Window does not exist"); }

  SDL_RaiseWindow(_window);
}

bool Window::hasFocus() const {
  if (!_window) { reportFatalError("Window does not exist"); }

  return SDL_GetWindowFlags(_window) & SDL_WINDOW_INPUT_FOCUS;
}

void Window::setDisplayMode(WindowDisplayMode mode) {
  if (!_window) { reportFatalError("Window does not exist"); }

  if (_disp_mode == mode) return;

  if (_disp_mode == WindowDisplayMode::HIDDEN) { SDL_ShowWindow(_window); }

  if (_disp_mode == WindowDisplayMode::FULLSCREEN) { SDL_SetWindowFullscreen(_window, false); }

  switch (mode) {
    case WindowDisplayMode::HIDDEN:
      SDL_HideWindow(_window);
      break;
    case WindowDisplayMode::FULLSCREEN:
      SDL_SetWindowFullscreen(_window, true);
      break;
    case WindowDisplayMode::WINDOWED_BORDERED:
      SDL_SetWindowBordered(_window, true);
      break;
    case WindowDisplayMode::WINDOWED_BORDERLESS:
      SDL_SetWindowBordered(_window, false);
      break;
  }
}

WindowDisplayMode Window::getDisplayMode() const {
  return _disp_mode;
}

void Window::draw() {
  renderer->render(scene);
}