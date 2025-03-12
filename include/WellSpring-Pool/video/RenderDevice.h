#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_gpu.h>
#include <core/core.h>
#include <video/Window.h>
#include <vector>

typedef size_t Window_GPURID;

// You MUST only create one of these, and have multiple renderers
class RenderDevice : public Stationary {
  SDL_GPUDevice *_sdl_gpu;

  std::vector<Window *> _bound_windows;

public:
  RenderDevice();
  ~RenderDevice();

  Window_GPURID bindWindow(Window &);

  SDL_Window *getSDLWindow(Window_GPURID);

  SDL_GPUDevice *getSDLPtr();
};