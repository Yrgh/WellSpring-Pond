#include <events.h>
#include <engine/clocks.h>
#include <engine/AutoServicer.h>
#include <engine/ThreadGen.h>
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
        AutoServicer services;
        ThreadGenerator threads;

        Engine() {
            // ThreadGenerator::destroy will wait for threads to finish, so we have to stop the endless loop in services
            // We can't cancel std::threads so make sure not to have endless loops 
            shutdown.subscribe(Callable<void()>(BIND_METHOD(services, stop)));
            shutdown.subscribe(Callable<void()>(BIND_METHOD(threads, destroy)));
        }

        // My favorite phrase: YNK
        ~Engine() { shutdown.call(); }
    };
}

extern WellSpring::Engine engine;