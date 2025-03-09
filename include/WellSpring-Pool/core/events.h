#pragma once
#include <core/QueueList.h>
#include <core/Callable.h>

// Allows you to call multiple function pointers at a time
template<typename ...Args> class Event {
public:
    using Listener = Callable<void(Args...)>;
private:
    QueueList<Listener> _listeners;
    
    typedef typename QueueList<Listener>::Element Element;
public:
    inline bool isSubscribed(const Listener &listener) const {
        const Element *el = _listeners.head;
        while (el) {
            if (el->value == listener) return true;
            el = el->next;
        }
        return false;
    }
    
    inline void subscribe(const Listener &listener) {
        if (isSubscribed(listener)) return;
        _listeners.push(listener);
    }
    
    inline void unsubscribe(const Listener &listener) {
        if (!_listeners.head) return;
        if (_listeners.head->value == listener) {
            _listeners.pop();
            return;
        }

        const Element *el = _listeners.head->next;
        const Element *last = _listeners.head;
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
        if (!_listeners.head) {return;}
        const Element *el = _listeners.head;
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
private:
    QueueList<Listener> _listeners;
    
    typedef typename QueueList<Listener>::Element Element;
public:
    inline bool isSubscribed(const Listener &listener) const {
        const Element *el = _listeners.head;
        while (el) {
            if (el->value == listener) return true;
            el = el->next;
        }
        return false;
    }
    
    inline void subscribe(const Listener &listener) {
        if (is_subscribed(listener)) return;
        _listeners.push(listener);
    }
    
    inline void unsubscribe(const Listener &listener) {
        if (!_listeners.head) return;
        if (_listeners.head->value == listener) {
            _listeners.pop();
            return;
        }

        const Element *el = _listeners.head->next;
        const Element *last = _listeners.head;
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
        if (!_listeners.head) {return false;}
        Element *el = _listeners.head;
        while (el != nullptr) {
            if (el->value(args...)) return true;
            el = el->next;
        }
        return false;
    }
};
