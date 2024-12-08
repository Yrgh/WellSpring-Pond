#include <engine/AutoServicer.h>

void AutoServicer::process() {
    state = STARTED;
    while (state != STOPPED) {
        if (state == WAIT) continue;
        for (int i = 0; i < in_use; ++i) {
            Service &service = services[i];
            if (get_ms_since(service.last) >= service.delay) {
                service.last = TimePoint::now();
                service.func();
            }
        }
    }
}

void AutoServicer::add(int d, Callable<void()> f) {
    if (state == STARTED) state = WAIT;
    if (allocated < in_use + 1) {
        allocated = allocated < 8 ? 8 : allocated * 2;
        services = (Service *) realloc(services, allocated * sizeof(Service));
    }
    Service &service = services[in_use];
    service.func = f;
    service.delay = d;
    service.last = TimePoint::now();
    in_use++;
    if (state == WAIT) state = STARTED;
}