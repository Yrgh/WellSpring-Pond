#pragma once
#include <SDL3/SDL.h>
#include <core/core.h>
#include <scene/Scene.h>
#include <video/Renderer.h>
#include <core/math_renames.h>

enum class WindowDisplayMode {
  HIDDEN,
  FULLSCREEN,
  WINDOWED_BORDERED,
  WINDOWED_BORDERLESS,
};

class Window : public Stationary {
private:
  SDL_Window *_window;

  Event<Window *> _on_destroy;

  friend class Renderer;

  Window *_parent;

  WindowDisplayMode _disp_mode = WindowDisplayMode::WINDOWED_BORDERED;
public:
  Renderer *renderer;

  Scene scene;

  // Creates a window
  Window(int w, int h, uint64_t sdl_flags, Renderer *renderer);
  Window();
  ~Window();

  bool hasParent() const;
  Window &getParent();
  void setParent(const Window &);
  void deparent();

  SDL_Window *getSDLPtr();

  Vec2i getSize() const;
  void setSize(const Vec2i &);

  Vec2i getPosition() const;
  void setPosition(const Vec2i &);

  // Grabs the users attention. On Windows, it makes the window's icon blink red
  void flashUntilFocused();
  void flashTemporarily();

  // Brings the window to the front and makes it input-focused
  void focus();
  bool hasFocus() const;
  
  // Changes how the window is displayed
  void setDisplayMode(WindowDisplayMode);
  WindowDisplayMode getDisplayMode() const;

  void draw();
};