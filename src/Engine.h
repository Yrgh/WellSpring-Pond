#include "events.h"
#include <SDL3/SDL.h>
#include <chrono>
namespace chrono = std::chrono;

#define STATIC_MEMBER_DECLARE(member) decltype(member) member;

#define OP_EQUALS(type1, type2, op)         \
type1 &operator op##=(const type2 &other) { \
    *this = operator op(other);             \
    return *this;                           \
}

namespace WellSpring {
    class TimePoint;

    class Duration {
    private:
        chrono::nanoseconds duration;
        friend class TimePoint;
    public:
        Duration(const chrono::nanoseconds &us) : duration(us) {}
        Duration() {}

        inline int get_ms() const     {
            return chrono::duration_cast<chrono::milliseconds>(duration).count();
        }
        inline float get_secs() const { return float(duration.count()) * 1e-9; }
        
        inline static Duration from_us(int us) {
            Duration dur;
            dur.duration = chrono::nanoseconds(us);
            return dur;
        }

        inline static Duration from_ms(int ms) {
            return from_us(ms * 1000);
        }
        
        inline Duration operator+(const Duration &other) {
            return Duration::from_us(duration.count() + other.duration.count());
        }

        inline Duration operator-(const Duration &other) {
            return Duration::from_us(duration.count() - other.duration.count());
        }

        OP_EQUALS(Duration, Duration, +)
        OP_EQUALS(Duration, Duration, -)
    };

    class TimePoint {
    private:
        chrono::high_resolution_clock::time_point point;
        friend class Clock;
    public:
        TimePoint(const chrono::high_resolution_clock::time_point &time) : point(time) {}
        TimePoint() {}

        static TimePoint now() { return TimePoint(chrono::high_resolution_clock::now()); }

        // end-start
        Duration operator-(const TimePoint &other) const {
            return Duration(chrono::duration_cast<chrono::milliseconds>(point - other.point));
        }

        TimePoint operator+(const Duration &other) const {
            return TimePoint(point + other.duration);
        }

        TimePoint operator-(const Duration &other) const {
            return TimePoint(point - other.duration);
        }

        OP_EQUALS(TimePoint, Duration, +)
        OP_EQUALS(TimePoint, Duration, -)
    };

    class Clock {
    private:
        TimePoint start_of_time;
        bool ticking = false;
    public:
        inline void restart() { start_of_time = TimePoint::now(); ticking = true; }
        inline int get_ms() const { return get_ms_since(TimePoint::now()); }
        inline float get_secs() const { return get_secs_since(TimePoint::now()); }
        int get_ms_since(const TimePoint &point) const;
        float get_secs_since(const TimePoint &point) const;
    };

    class Engine {
    private:
    public:
        // Triggered when an SDL event is polled
        EventUnhandled<const SDL_Event &> sdl_event_unhandled;
        // If one or more events is available execution will pause
        void pollSDLEvents();
        EventRaw<> shutdown;
        
        Clock clock;
    };
}

extern WellSpring::Engine engine;