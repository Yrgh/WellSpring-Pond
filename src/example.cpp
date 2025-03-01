#include <engine/Engine.h>
#include <iostream>
#include <video/Window.h>
#include <video/GenericSimpleRenderer.h>
#include <video/Vulkan/VulkanRenderDevice.h>

/* NOTE:
 * This is an example program. You may expand on this if you want
 */

int main(int argc, char **argv) {
  GenericSimpleRenderer renderer(new VulkanRenderDevice);

  Window window(640, 480, "Window", SDL_WINDOW_RESIZABLE, &renderer);
  
  bool should_continue = true;
  
  FunctorBox<void()> shutdown_box = [&]() {
    std::cout << "Oonnga Booga\n";
    should_continue = false;
    SDL_Quit();
  };
  
  engine.shutdown.subscribe(shutdown_box);

  engine.clock.restart();

  while (should_continue) {
    engine.poll_sdl_events();
  }

  return 0;
}