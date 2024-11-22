#pragma once
#include <string>

extern void reportFatalSDLError(const std::string &when);

extern void reportNonFatalSDLError(const std::string &when);

extern void reportFatalError(const std::string &error, int code = -2);

template<class ...Args> extern void log(Args... args);