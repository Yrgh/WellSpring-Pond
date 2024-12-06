#include <stdlib.h>
#include <stdint.h>
#include "Callable.h"
#include "clocks.h"

class AutoServicer {
private:
    struct Service {
        Callable<void()> func;
        int delay;
        TimePoint last;
    };
    uint32_t allocated = 0;
    uint32_t in_use = 0;
    Service *services = NULL;
    // A basic mutex. I'm a genius
    enum {
        STOPPED,
        STARTED,
        WAIT,
    } state;
public:
    void process();
    void add(int d, Callable<void()> f);
    inline void stop() { state = STARTED; }
    inline bool is_running() const { return state != STOPPED; }
};