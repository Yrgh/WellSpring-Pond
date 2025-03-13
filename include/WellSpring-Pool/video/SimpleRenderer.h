#pragma once
#include <video/Renderer.h>
#include <video/RenderDevice.h>

class SimpleRenderer : public Renderer {
protected:
  RenderDevice *_device = nullptr;

  SDL_GPUDevice *_sdl_gpu = nullptr;

  SDL_Window *_win = nullptr;

  uint32_t _last_screen_width = 0, _last_screen_height = 0;

  SDL_GPUTexture *_depth_stencil_buf = nullptr;
  
  void onWindowEncapsulation(Window &) override;

  struct ShaderInfo {

  };

  std::vector<ShaderInfo> _shaders;
  
public:
  SimpleRenderer() = default;

  SimpleRenderer(RenderDevice &);

  void render(const Scene &) override;

  Shader_RRID registerShader(const std::string &path,
    uint32_t samplers, uint32_t textures, uint32_t buffers, uint32_t uniforms
  ) override;
  void createPipeline(Shader_RRID vert, Shader_RRID frag) override;
};