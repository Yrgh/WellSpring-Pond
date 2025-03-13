#pragma once
#include <scene/Scene.h>
#include <core/classes.h>

class Window;

typedef size_t Shader_RRID;

// You must create exactly one of these per Window
class Renderer : public Stationary {
protected:

  friend class Window;
  Window *window;

  virtual void onWindowEncapsulation(Window &) = 0;
public:
  virtual void render(const Scene &) = 0;
  
  virtual Shader_RRID registerShader(const std::string &path,
    uint32_t samplers, uint32_t textures, uint32_t buffers, uint32_t uniforms
  ) = 0;
  virtual void createPipeline(Shader_RRID vert, Shader_RRID frag) = 0;
};