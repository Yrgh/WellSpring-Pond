#include <engine/Engine.h>
#include <util/error.h>

using namespace WellSpring;

void Engine::poll_sdl_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) shutdown.call();
        sdl_event_unhandled.call(event);
    }
}

Engine::Engine() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        reportFatalSDLError("when initializing video");
    }

    if (!SDL_Init(SDL_INIT_EVENTS)) {
        reportFatalSDLError("when initializing events");
    }

    if (!SDL_Init(SDL_INIT_AUDIO)) {
        reportFatalSDLError("when initializing audio");
    }
    // ThreadGenerator::destroy will wait for threads to finish, so we have to stop the endless loop in services
    // We can't cancel std::threads so make sure not to have endless loops 
    shutdown.subscribe(Callable<void()>(BIND_METHOD(services, stop)));
    shutdown.subscribe(Callable<void()>(BIND_METHOD(threads, destroy)));
}

Engine engine;