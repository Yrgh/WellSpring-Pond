#pragma once
#include <scene/Scene.h>
#include <core/classes.h>

class Window;

// You must create exactly one of these per Window
class Renderer : public Stationary {
protected:

  friend class Window;
  Window *window;

  virtual void onWindowEncapsulation(Window &) = 0;
public:
  virtual void render(const Scene &) = 0;
};