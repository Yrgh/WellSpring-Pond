#include <video/RenderDevice.h>

RenderDevice::RenderDevice() {
  _sdl_gpu = SDL_CreateGPUDevice(
    SDL_GPU_SHADERFORMAT_SPIRV,
#ifdef WSGLOBAL_DEBUG_MODE
    true
#else
    false
#endif
    , NULL
  );

  if (!_sdl_gpu) {
    reportFatalSDLError("when creating GPU device for RenderDevice");
  }
}

RenderDevice::~RenderDevice() {
  SDL_DestroyGPUDevice(_sdl_gpu);

  for (Window *w : _bound_windows) {
    SDL_ReleaseWindowFromGPUDevice(_sdl_gpu, w->getSDLPtr());
  }

  for (SDL_GPUGraphicsPipeline *g : _graphics_pipelines) {
    SDL_ReleaseGPUGraphicsPipeline(_sdl_gpu, g);
  }
}

SDL_GPUDevice *RenderDevice::getSDLPtr() {
  return _sdl_gpu;
}

SDL_GPUGraphicsPipeline *RenderDevice::generateGraphicsPipeline(SDL_GPUShaderCreateInfo vsi, SDL_GPUShaderCreateInfo fsi, GraphicsPipelineInfo &pip_info) {
  SDL_GPUShader *vs = SDL_CreateGPUShader(_sdl_gpu, &vsi);
  SDL_GPUShader *fs = SDL_CreateGPUShader(_sdl_gpu, &fsi);

  SDL_GPUGraphicsPipelineCreateInfo info = {};
  info.vertex_shader   = vs;
  info.fragment_shader = fs;
  info.target_info = {
    .color_target_descriptions = pip_info.color_target_descriptions,
    .num_color_targets = pip_info.num_color_targets,
  };
  info.rasterizer_state.cull_mode = SDL_GPU_CULLMODE_NONE;
  info.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;

  SDL_GPUGraphicsPipeline *pip = SDL_CreateGPUGraphicsPipeline(_sdl_gpu, &info);
  if (!pip) {
    reportFatalSDLError("when creating graphics pipeline");
  }

  _graphics_pipelines.push_back(pip);

  SDL_ReleaseGPUShader(_sdl_gpu, vs);
  SDL_ReleaseGPUShader(_sdl_gpu, fs);

  return pip;
}