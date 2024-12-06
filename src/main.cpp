#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Window.h"
#include "util/error.h"
#include "Engine.h"

#include "ThreadGen.h"

/* NOTE:
 * This is an example program. You may expand on this if you want
*/

int main(int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        reportFatalSDLError("when initializing video");
    }

    if (!SDL_Init(SDL_INIT_EVENTS)) {
        reportFatalSDLError("when initializing events");
    }

    if (!SDL_Init(SDL_INIT_AUDIO)) {
        reportFatalSDLError("when initializing audio");
    }

    Window window(640, 480, "Window", SDL_WINDOW_RESIZABLE);
    window.ready();

    engine.clock.restart();

    SDL_Event event;
    bool should_continue = true;
    engine.shutdown.subscribe(callable_lambda<void()>(
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