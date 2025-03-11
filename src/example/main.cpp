// These are important!
#define WSGLOBAL_APP_NAME Example
#define WSGLOBAL_APP_VERSION_MAJOR 1
#define WSGLOBAL_APP_VERSION_MINOR 0
#define WSGLOBAL_APP_VERSION_PATCH 0

#include <engine/Application.h>
#include <engine/time.h>
#include <iostream>
#include <video/GenericSimpleRenderer.h>
#include <video/RenderDevice.h>
#include <video/Window.h>
#include <optional>

const int stable_fps = 30;

class APP(Application) {
  std::optional<RenderDevice> device;
  std::optional<GenericSimpleRenderer> renderer;
  std::optional<Window> window;
public:
  void init() {
    device.emplace();
    renderer.emplace(device.value());
    window.emplace(640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN, &(renderer.value()));

    window.value().flashTemporarily();
  }

  void close() {
    window.reset();
    renderer.reset();
    device.reset();
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