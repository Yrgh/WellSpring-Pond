#include <video/SimpleRenderer.h>

SimpleRenderer::SimpleRenderer(RenderDevice &rd) : _device(&rd) {
  _sdl_gpu = rd.getSDLPtr();
}

#include <iostream>

void SimpleRenderer::render(const Scene &) {
  std::cout << "render()...\n";

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

  // Add the swapchain texture as the color target
  SDL_GPUColorTargetInfo col_targ_infos[] = {
    {
      .texture     = swapchain,
      .clear_color = SDL_FColor{0.0f, 0.0f, 1.0f, 1.0f}, // Blue
      .load_op     = SDL_GPU_LOADOP_CLEAR,
      .store_op    = SDL_GPU_STOREOP_STORE,
     }
  };

  // We have to recreate the screen buffers
  if (_last_screen_width != display_x || _last_screen_height != display_y) {
    std::cout << "New screen\n";

    // Out with the old... (potentially)
    if (_depth_stencil_buf) {
      SDL_ReleaseGPUTexture(_sdl_gpu, _depth_stencil_buf);
    }

    // Create the depth/stencil buffer and use it as an attachment
    SDL_GPUTextureCreateInfo depth_stencil_create_info = {
      .type                 = SDL_GPU_TEXTURETYPE_2D,
      .format               = SDL_GPU_TEXTUREFORMAT_D24_UNORM_S8_UINT,
      .usage                = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
      .width                = display_x,
      .height               = display_y,
      .layer_count_or_depth = 1, // 2D
    };

    // In with the new
    _depth_stencil_buf = SDL_CreateGPUTexture(_sdl_gpu, &depth_stencil_create_info);

    if (!_depth_stencil_buf) {
      reportFatalSDLError("when creating depth/stencil buffer");
    }

    std::cout << "New screen complete\n";
  }

  SDL_GPUDepthStencilTargetInfo depth_stencil_targ_info = {
    .texture          = _depth_stencil_buf,
    .clear_depth      = 1.0f,
    .load_op          = SDL_GPU_LOADOP_CLEAR,
    .store_op         = SDL_GPU_STOREOP_DONT_CARE, // Change this if you need the depth buffer later
    .stencil_load_op  = SDL_GPU_LOADOP_CLEAR,
    .stencil_store_op = SDL_GPU_STOREOP_DONT_CARE, // Again, but less likely
    .cycle            = true,
    .clear_stencil    = 0,
  };

  std::cout << "Render pass\n";

  SDL_GPURenderPass *rp = SDL_BeginGPURenderPass(
    cmd_buf,
    col_targ_infos, (uint32_t) C_ARR_SIZE(col_targ_infos),
    &depth_stencil_targ_info
  );

  std::cout << "Render pass began\n";

  if (!rp) {
    reportFatalSDLError("when creating render pass");
  }
  
  SDL_EndGPURenderPass(rp);

  std::cout << "Submitting..\n";

  SDL_SubmitGPUCommandBuffer(cmd_buf);

  _last_screen_width  = display_x;
  _last_screen_height = display_y;
  std::cout << "Done\n";
}

void SimpleRenderer::onWindowEncapsulation(Window &win) {
  _device->bindWindow(win);
  _win = win.getSDLPtr();
}