#include <iostream>
#include <Window.h>
#include <engine/Engine.h>

/* NOTE:
 * This is an example program. You may expand on this if you want
*/

int main(int argc, char **argv) {
    Window window(640, 480, "Window", SDL_WINDOW_RESIZABLE);
    window.ready();

    engine.clock.restart();

    bool should_continue = true;
    engine.shutdown.subscribe(generateCallable<void()>(
        [&](){
            should_continue = false;
            
            SDL_Quit();
        }
    ));

    while (should_continue) {
        engine.poll_sdl_events();
    }

    return 0;
}