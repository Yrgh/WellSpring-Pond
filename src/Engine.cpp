#include "Engine.h"
#include "util/error.h"

using namespace WellSpring;

void Engine::poll_sdl_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) shutdown.call();
        sdl_event_unhandled.call(event);
    }
}

Engine engine;