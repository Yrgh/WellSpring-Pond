#pragma once
#include <thread>
#include <vector>
#include <core/RoundQueue.h>
#include <core/Callable.h>

// NOTE: NEVER EVER DISPATCH AN ENDLESS LOOP WITH NO WAY TO STOP IT!!!!!!!!

namespace WellSpring {
    class ThreadGenerator {
    private:
        std::vector<std::thread *> threads;
        int max_threads = std::thread::hardware_concurrency();
        friend class Engine;

        void destroy() {
            for (std::thread *t : threads) {
                t->join();
                delete t;
            }
        }
    public:
        template <typename T, class... Args> int dispatch(const T &func, Args...args)  {
            for (int i = 0; i < threads.size(); ++i) {
                if (!(threads[i]->joinable())) {
                    delete threads[i];
                    threads[i] = new std::thread(func, args...);
                    return i;
                }
            }

            if (threads.size() < max_threads) {
                threads.push_back(new std::thread(func, args...));
                return threads.size() - 1;
            }

            func(args...);
            return -1;
        }

        ~ThreadGenerator() {
            destroy();
        }

        inline int get_max_threads() const  {
            return max_threads; 
        }
        inline int set_max_threads(int num) {
            return max_threads = (threads.size() > num) ? threads.size() : num;
        }
    };
}