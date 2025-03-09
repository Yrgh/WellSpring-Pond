#include <engine/Application.h>
#include <engine/time.h>
#include <iostream>
#include <video/GenericSimpleRenderer.h>
#include <video/Vulkan/VulkanRenderDevice.h>
#include <video/Window.h>
#include <optional>

const int stable_fps = 30;

class APP(Application) {
  std::optional<VulkanRenderDevice> device;
  std::optional<GenericSimpleRenderer> renderer;
  std::optional<Window> window;
public:
  void init() {
    device.emplace();
    device.value().initSystem();
    renderer.emplace(&(device.value()));
    window.emplace(640, 480, "Window", SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN, &(renderer.value()));

    window.value().flashTemporarily();
  }

  void close() {
    device.value().cleanupSystem();
  }

  void stableTick() {

  }

  void renderTick() {
    window.value().draw();
  }

  void onInputFrame() {

  }
};

int main(int argc, char **argv) {
  Application app;
  app.run();
  std::cout << "App done\n";

  return 0;
}