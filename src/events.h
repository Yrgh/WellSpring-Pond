#include "util/QueueList.h"
#include "callable.h"

// NOTE: I had to add "(Listener)" because the compiler didn't like it

// NOTE: Events are currently wonky! It is important that you only use one memory address to store a given functor!

// Allows you to call multiple function pointers at a time
template<typename ...Args> class Event {
public:
    using Listener = Callable<void(Args...)>;
    
    QueueList<Listener> listeners;
    
    typedef typename QueueList<Listener>::Element Element;
    
    inline bool is_subscribed(const Listener &listener) {
        Element *el = listeners.head;
        while (el) {
            if (el->value == listener) return true;
            el = el->next;
        }
        return false;
    }
    
    inline void subscribe(const Listener &listener) {
        if (is_subscribed(listener)) return;
        listeners.push(listener);
    }
    
    inline void unsubscribe(const Listener &listener) {
        if (!listeners.head) return;
        if (listeners.head->value == listener) {
            listeners.pop();
            return;
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
template<typename ...Args> class UnhandledEvent {
public:
    using Listener = Callable<bool(Args...)>;
    
    QueueList<Listener> listeners;
    
    typedef typename QueueList<Listener>::Element Element;

    inline bool is_subscribed(const Listener &listener) {
        Element *el = listeners.head;
        while (el) {
            if (el->value == listener) return true;
            el = el->next;
        }
        return false;
    }
    
    inline void subscribe(const Listener &listener) {
        if (is_subscribed(listener)) return;
        listeners.push(listener);
    }
    
    inline void unsubscribe(const Listener &listener) {
        if (!listeners.head) return;
        if (listeners.head->value == listener) {
            listeners.pop();
            return;
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
