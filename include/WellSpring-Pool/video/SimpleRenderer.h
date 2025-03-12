#pragma once
#include <video/Renderer.h>
#include <video/RenderDevice.h>

class SimpleRenderer : public Renderer {
protected:
  RenderDevice *_device;

  SDL_GPUDevice *_sdl_gpu;

  SDL_Window *_win;

  uint32_t _last_screen_width = 0, _last_screen_height = 0;

  SDL_GPUTexture *_depth_stencil_buf;
  
  void onWindowEncapsulation(Window &) override;
  
public:
  SimpleRenderer() = default;

  SimpleRenderer(RenderDevice &);

  void render(const Scene &) override;
};