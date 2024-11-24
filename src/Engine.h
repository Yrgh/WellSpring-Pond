#include "events.h"
#include <SDL3/SDL.h>

#define STATIC_MEMBER_DECLARE(member) decltype(member) member;

// You never need to instantiate this
// TODO: Should this file include all main components?
class Engine {
private:
public:
    // Triggered when an SDL event is polled
    static EventUnhandled<const SDL_Event &> sdl_event_unhandled;
    // If one or more events is available execution will pause
    static void pollSDLEvents();
    static EventRaw<> shutdown;
};