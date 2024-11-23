#include "QueueList.h"

// Allows you to call multiple function pointers at a time
template<typename ...Args> class EventRaw {
public:
    using Listener = void (*)(Args...);
    
    QueueList<Listener> listeners;
    
    typedef typename QueueList<Listener>::Element Element;
    
    inline void subscribe(Listener listener) {
        listeners.push(listener);
    }
    
    inline void unsubscribe(Listener listener) {
        if (!listeners.head) {return;}
        if (listeners.head->value == listener) {
            listeners.pop();
        }
        Element *el = listeners.head->next;
        Element *last = listeners.head;
        while (el != nullptr) {
            if (el->value == listener) {
                last->next = el->next;
                delete el;
            }
            last = el;
            el = el->next;
        }
    }
    
    inline void call(Args... args) const {
        if (!listeners.head) {return;}
        Element *el = listeners.head;
        while (el != nullptr) {
            el->value(args...);
            el = el->next;
        }
    }
};

/* Allows you to call function pointers until one handles the event. The order added is the order called.
 * Do not subscribe functions that could/will modify inputs or perform external actions yet not handle the event.
*/
template<typename ...Args> class EventUnhandled {
public:
    using Listener = bool (*)(Args...);
    
    QueueList<Listener> listeners;
    
    typedef typename QueueList<Listener>::Element Element;
    
    inline void subscribe(Listener listener) {
        listeners.push(listener);
    }
    
    inline void unsubscribe(Listener listener) {
        if (!listeners.head) {return;}
        if (listeners.head->value == listener) {
            listeners.pop();
        }
        Element *el = listeners.head->next;
        Element *last = listeners.head;
        while (el != nullptr) {
            if (el->value == listener) {
                last->next = el->next;
                delete el;
            }
            last = el;
            el = el->next;
        }
    }
    
    inline bool call(Args... args) const {
        if (!listeners.head) {return false;}
        Element *el = listeners.head;
        while (el != nullptr) {
            if (el->value(args...)) return true;
            el = el->next;
        }
        return false;
    }
};
