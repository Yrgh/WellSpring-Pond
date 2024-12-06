#include "events.h"
#include "clocks.h"
#include <SDL3/SDL.h>

#define STATIC_MEMBER_DECLARE(member) decltype(member) member;

namespace WellSpring {
    class Engine {
    private:
    public:
        // Triggered when an SDL event is polled
        UnhandledEvent<const SDL_Event &> sdl_event_unhandled;
        // If one or more events is available execution will pause
        void poll_sdl_events();
        Event<> shutdown;
        
        Clock clock;
    };
}

extern WellSpring::Engine engine;