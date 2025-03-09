#pragma once
#include <engine/time.h>

// Define class APP_NAME to create your app!

template <class Derived> class BaseApplication {
  int  fps_ms = 1; // 1000 fps
  bool live;

  TimePoint last_render, last_stable;

protected:
  // Started immediately before init is called
  Clock clock;

  // TODO:
  struct InputEvent {
    enum {
      
    } type;

    union {

    };
  };

public:
  // Called before looping
  void init();

  // Called after the loop finishes
  void close();

  // Called at a rate dependent on the render delta/FPS
  void renderTick();

  void setRenderFPS(int);
  int  getRenderFPS() const;

  // These incur slightly more overhead
  void  setRenderDeltaSecs(float);
  float getRenderDeltaSecs() const;

  // These incur slightly less overhed
  void setRenderDeltaMs(int);
  int  getRenderDeltaMs() const;

  // Called every 33ms, unless specified by the STABLE_SPEED macro
  void stableTick();

  // Called any frame where an input event is received, regardless of what the maximum FPS is
  // Avoid putting too much logic in here, as it can slow down input handling
  void onInputFrame();

  // Quits the loop on the next frame
  void terminate();

  void run();
};

#define APP(name) \
  name:           \
public            \
  BaseApplication<name>

#ifndef STABLE_SPEED
#define STABLE_SPEED 33
#endif

// Template instantiations
#pragma region IMPL

#include <SDL3/SDL.h>
#include <core/core.h>

#define TEMPLATE template <class T>
#define APP_T    BaseApplication<T>
#define APP_THIS (static_cast<T *>(this))

TEMPLATE
void APP_T::setRenderFPS(int fps) {
  fps_ms = 1000 / fps;
}

TEMPLATE
int APP_T::getRenderFPS() const {
  return 1000 / fps_ms;
}

TEMPLATE
void APP_T::setRenderDeltaSecs(float d) {
  fps_ms = 1.0e3f * d;
}

TEMPLATE
float APP_T::getRenderDeltaSecs() const {
  return (float)fps_ms / 1.0e3f;
}

TEMPLATE
void APP_T::setRenderDeltaMs(int ms) {
  fps_ms = ms;
}

TEMPLATE
int APP_T::getRenderDeltaMs() const {
  return fps_ms;
}

TEMPLATE
void APP_T::terminate() {
  live = false;
}

#include <iostream>

TEMPLATE
void APP_T::run() {
  static SDL_Event event;

  live = true;

  if (!SDL_Init(SDL_INIT_VIDEO)) { reportFatalSDLError("when initializing video"); }

  if (!SDL_Init(SDL_INIT_EVENTS)) { reportFatalSDLError("when initializing events"); }

  if (!SDL_Init(SDL_INIT_AUDIO)) { reportFatalSDLError("when initializing audio"); }

  clock.restart();

  APP_THIS->init();

  while (live) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        terminate();
      }
    }

    if (getMsSince(last_render) >= fps_ms) {
      dispatchThread(&T::renderTick, APP_THIS);
    }

    if (getMsSince(last_stable) >= STABLE_SPEED) {
      dispatchThread(&T::stableTick, APP_THIS);
    }
  }

  APP_THIS->close();
}

#undef APP_T
#undef TEMPLATE
#undef APP_THIS

#pragma endregion IMPL