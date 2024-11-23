#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Window.h"
#include "utils/error.h"
#include "Engine.h"

/* NOTE:
 * This is an example program. You may expand on this if you want
*/

int main(int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        reportFatalSDLError("when initializing video");
    }

    Window window(640, 480, "Window", 0);
    window.ready();

    SDL_Event event;
    bool should_continue = true;
    Engine::shutdown.subscribe([&should_continue](){
        should_continue = false;
    });
    while (should_continue) {
        Engine::pollSDLEvents();
    }

    return 0;
}