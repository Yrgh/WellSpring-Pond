#include <video/SimpleRenderer.h>

SimpleRenderer::SimpleRenderer(RenderDevice &rd) : _device(&rd) {
  _sdl_gpu = rd.getSDLPtr();
}

#include <iostream>

void SimpleRenderer::render(const Scene &) {

  SDL_GPUCommandBuffer *cmd_buf = SDL_AcquireGPUCommandBuffer(_sdl_gpu);
  if (!cmd_buf) {
    reportFatalSDLError("when acquiring GPU command buffer");
  }

  // Acquire the swapchain. Waiting is important, apparently, and we need the width and height for other things.

  SDL_GPUTexture *swapchain;
  uint32_t        display_x, display_y;
  if (!SDL_WaitAndAcquireGPUSwapchainTexture(cmd_buf, _win, &swapchain, &display_x, &display_y)) {
    reportFatalSDLError("when acquiring GPU swapchain");
  }

  if (!swapchain) {
    // This is OK. It occurs if the window is not being displayed.
    return;
  }

  // We have to recreate the screen buffers
  if (!_depth_stencil_buf ||_last_screen_width != display_x || _last_screen_height != display_y) {

    // Out with the old... (potentially)
    if (_depth_stencil_buf) {
      SDL_ReleaseGPUTexture(_sdl_gpu, _depth_stencil_buf);
    }

    // Create the depth/stencil buffer and use it as an attachment
    SDL_GPUTextureCreateInfo depth_stencil_create_info = {};
    depth_stencil_create_info.type                 = SDL_GPU_TEXTURETYPE_2D;
    depth_stencil_create_info.format               = SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT;
    depth_stencil_create_info.usage                = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET;
    depth_stencil_create_info.width                = display_x;
    depth_stencil_create_info.height               = display_y;
    depth_stencil_create_info.layer_count_or_depth = 1; // 2D
    depth_stencil_create_info.num_levels           = 1;
    depth_stencil_create_info.sample_count         = SDL_GPU_SAMPLECOUNT_1;
    depth_stencil_create_info.props                = 0;

    // In with the new
    _depth_stencil_buf = SDL_CreateGPUTexture(_sdl_gpu, &depth_stencil_create_info);

    if (!_depth_stencil_buf) {
      reportFatalSDLError("when creating depth/stencil buffer");
    }

    std::cout << "New screen complete\n";
  }

  static SDL_GPUDepthStencilTargetInfo depth_stencil_targ_info = {};
  depth_stencil_targ_info.texture          = _depth_stencil_buf;
  depth_stencil_targ_info.clear_depth      = 1.0f;
  depth_stencil_targ_info.load_op          = SDL_GPU_LOADOP_CLEAR;
  depth_stencil_targ_info.store_op         = SDL_GPU_STOREOP_DONT_CARE; // Change this if you need the depth buffer later
  depth_stencil_targ_info.stencil_load_op  = SDL_GPU_LOADOP_CLEAR;
  depth_stencil_targ_info.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE; // Again, but less likely
  depth_stencil_targ_info.cycle            = true;
  depth_stencil_targ_info.clear_stencil    = 0;

  // Add the swapchain texture as the color target
  static SDL_GPUColorTargetInfo col_targ_infos[] = {{}};
  col_targ_infos[0].texture     = swapchain;
  col_targ_infos[0].clear_color = SDL_FColor{0.0f, 0.0f, 1.0f, 1.0f}; // Blue
  col_targ_infos[0].load_op     = SDL_GPU_LOADOP_CLEAR;
  col_targ_infos[0].store_op    = SDL_GPU_STOREOP_STORE;
  col_targ_infos[0].cycle       = true;

  SDL_GPURenderPass *rp = SDL_BeginGPURenderPass(
    cmd_buf,
    col_targ_infos, (uint32_t) C_ARR_SIZE(col_targ_infos),
    &depth_stencil_targ_info
  );

  if (!rp) {
    reportFatalSDLError("when creating render pass");
  }

  // Render the scene
  
  SDL_EndGPURenderPass(rp);

  SDL_SubmitGPUCommandBuffer(cmd_buf);

  _last_screen_width  = display_x;
  _last_screen_height = display_y;
}

void SimpleRenderer::onWindowEncapsulation(Window &win) {
  _device->bindWindow(win);
  _win = win.getSDLPtr();
}

void SimpleRenderer::createPipeline(Shader_RRID vert, Shader_RRID frag) {
  SDL_GPUShaderCreateInfo vsi = {};
  vsi.format = SDL_GPU_SHADERTYPE_VERTEX;
  vsi.code = 
}