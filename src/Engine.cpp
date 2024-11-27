#include "Engine.h"
#include "util/error.h"

using namespace WellSpring;

void Engine::pollSDLEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) shutdown.call();
        sdl_event_unhandled.call(event);
    }
}

int Clock::get_ms_since(const TimePoint &point) const {
    if (!ticking) return 0;
    return (point - start_of_time).get_ms();
}

float Clock::get_secs_since(const TimePoint &point) const {
    if (!ticking) return 0;
    return (point - start_of_time).get_secs();
}

Engine engine;