#include <iostream>
#include <video/Window.h>
#include <engine/Engine.h>

/* NOTE:
 * This is an example program. You may expand on this if you want
 */

int main(int argc, char **argv)
{
  Window window(640, 480, "Window", SDL_WINDOW_RESIZABLE);
  window.ready();

  engine.clock.restart();

  bool should_continue = true;
  FunctorBox<void()> shutdown_box = [&]() {
    std::cout << "Oonnga Booga\n";
    should_continue = false;
    SDL_Quit();
  };

  engine.shutdown.subscribe(shutdown_box);

  while (should_continue) {
    engine.poll_sdl_events();
  }

  return 0;
}