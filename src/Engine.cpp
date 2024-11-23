#include "Engine.h"
#include "utils/error.h"

void Engine::pollSDLEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) shutdown.call();
        sdl_event_unhandled.call(event);
    }
}

STATIC_MEMBER_DECLARE(Engine::shutdown)
STATIC_MEMBER_DECLARE(Engine::sdl_event_unhandled)