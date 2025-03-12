// These are important!
#define WSGLOBAL_APP_NAME Example
#define WSGLOBAL_APP_VERSION_MAJOR 1
#define WSGLOBAL_APP_VERSION_MINOR 0
#define WSGLOBAL_APP_VERSION_PATCH 0
#define WSGLOBAL_DEBUG_MODE

#include <engine/Application.h>
#include <engine/time.h>
#include <iostream>
#include <video/SimpleRenderer.h>
#include <video/RenderDevice.h>
#include <video/Window.h>
#include <optional>

const int stable_fps = 30;

class APP(Application) {
  std::optional<RenderDevice> device;
  std::optional<SimpleRenderer> renderer;
  std::optional<Window> window;

  bool done_drawing = true;

public:
  void init() {
    device.emplace();
    renderer.emplace(device.value());
    window.emplace(640, 480, SDL_WINDOW_RESIZABLE, &(renderer.value()));

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
    if (done_drawing) {
      done_drawing = false;
      window.value().draw();
      done_drawing = true;
    }
  }

  void onInputFrame() {

  }
};

int main(int argc, char **argv) {
  SDL_SetHint(SDL_HINT_RENDER_VULKAN_DEBUG, "1");

  Application app;
  app.run();
  std::cout << "App done\n";

  return 0;
}