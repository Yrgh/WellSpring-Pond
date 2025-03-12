#pragma once
#define STRINIGFY(arg) #arg
#define C_ARR_SIZE(arr) (sizeof(arr)/sizeof(*arr))

#include <core/classes.h>
#include <core/Callable.h>
#include <core/error.h>
#include <core/events.h>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>
#include <thread>

template <class T, class... Args> void dispatchThread(const T &f, Args... args) {
  std::thread t(f, args...);
  t.detach();
}