#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Window.h"
#include "utils/error.h"

/* NOTE:
 * 
*/

int main(int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        reportFatalSDLError("when initializing video");
    }

    Window window(640, 480, "Window", 0);
    window.ready();

    SDL_Event event;
    bool should_continue = true;
    while (should_continue) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                should_continue = false;
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                // The primary window was closed. SDL may already do this, but this is just to be sure
                if (event.window.windowID == SDL_GetWindowID(window.get_sdl_ptr())) {
                    SDL_Quit();
                    should_continue = false;
                }
                break;
            }
        }
    }

    return 0;
}