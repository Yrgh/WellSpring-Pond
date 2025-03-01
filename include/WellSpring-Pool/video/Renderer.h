#pragma once
#include <scene/Scene.h>

class Window;

// Polymorphic class. We don't need RTTI, so we aren't going to add it.
class Renderer {
protected:

  friend class Window;
  Window *window;
public:
  virtual void render(const Scene &) = 0;

};