#include <engine/time.h>

void Clock::restart() {
    start_of_time = TimePoint::now();
    ticking = true;
}

int Clock::getMs() const {
    if (!ticking) return 0;
    return getMsSince(start_of_time);
}

float Clock::getSecs() const {
    if (!ticking) return 0;
    return getSecsSince(start_of_time);
}

int getMsSince(const TimePoint &point) {
    return (TimePoint::now() - point).getMs();
}

float getSecsSince(const TimePoint &point) {
    return (TimePoint::now() - point).getSecs();
}