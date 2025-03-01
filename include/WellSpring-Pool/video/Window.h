#pragma once
#include <SDL3/SDL.h>
#include <core/events.h>
#include <scene/Scene.h>
#include <string>
#include <video/Renderer.h>

class Window {
private:
  SDL_Window *_window;

  Event<Window *> _on_destroy;

  friend class Renderer;
public:
  Renderer *renderer;

  Scene scene;

  // Creates a window
  Window(int w, int h, const std::string &name, uint64_t sdl_flags, Renderer *renderer);
  Window();
  ~Window();

  Window(const Window &)            = delete;
  Window &operator=(const Window &) = delete;
  Window(Window &&)            = delete;
  Window &operator=(Window &&) = delete;

  SDL_Window *getSDLPtr();

  void draw();
};