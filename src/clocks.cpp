#include "clocks.h"

void WellSpring::Clock::restart() {
    start_of_time = TimePoint::now();
    ticking = true;
}

int WellSpring::Clock::get_ms() const {
    if (!ticking) return 0;
    return get_ms_since(start_of_time);
}

float WellSpring::Clock::get_secs() const {
    if (!ticking) return 0;
    return get_secs_since(start_of_time);
}

int WellSpring::Clock::get_ms_since(const TimePoint &point) {
    return (TimePoint::now() - point).get_ms();
}

float WellSpring::Clock::get_secs_since(const TimePoint &point) {
    return (TimePoint::now() - point).get_secs();
}