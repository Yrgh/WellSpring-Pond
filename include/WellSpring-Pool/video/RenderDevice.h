#pragma once
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_gpu.h>
#include <core/core.h>
#include <video/Window.h>
#include <vector>

struct GraphicsPipelineInfo {
  uint32_t num_color_targets;
  SDL_GPUColorTargetDescription *color_target_descriptions;
};

// You MUST only create one of these, and have multiple renderers
class RenderDevice : public Stationary {
  SDL_GPUDevice *_sdl_gpu;

  std::vector<Window *> _bound_windows;

  std::vector<SDL_GPUGraphicsPipeline *> _graphics_pipelines;

public:
  RenderDevice();
  ~RenderDevice();

  SDL_Window *bindWindow(Window &);

  SDL_GPUDevice *getSDLPtr();

  SDL_GPUGraphicsPipeline *generateGraphicsPipeline(SDL_GPUShaderCreateInfo vsi, SDL_GPUShaderCreateInfo fsi, GraphicsPipelineInfo &info);
};