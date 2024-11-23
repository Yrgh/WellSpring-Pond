#include <stdexcept>

// Implements a queue through a linked list, but exposes the pointers for your leisure
template<class T> class QueueList {
public:
    inline ~QueueList() {
        Element *current = head;
        while (current) {
            Element *next = current->next;
            delete current;
            current = next;
        }
    }
    
    struct Element {
        Element *next;
        T value;
    };
    
    Element *head = nullptr, *tail = nullptr;
    
    inline void push(T v) {
        Element *el = new Element{nullptr, v};
        if (!head) {
            head = el;
            tail = el;
            return;
        }
        tail->next = el;
        tail = el;
    }
    
    inline T pop() {
        if (!head) throw std::length_error("Empty list!");
        if (head == tail) {
            T v = head->value;
            delete head;
            head = nullptr;
            tail = nullptr;
            return v;
        }
        Element e = *head;
        delete head;
        head = e.next;
        return e.value;
    }
};
