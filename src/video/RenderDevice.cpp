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
}

SDL_Window *RenderDevice::getSDLWindow(Window_GPURID rid) {
  return _bound_windows[rid]->getSDLPtr();
}

Window_GPURID RenderDevice::bindWindow(Window &win) {
  SDL_ClaimWindowForGPUDevice(_sdl_gpu, win.getSDLPtr());

  Window_GPURID id = _bound_windows.size();
  _bound_windows.push_back(&win);

  return id;
}

SDL_GPUDevice *RenderDevice::getSDLPtr() {
  return _sdl_gpu;
}