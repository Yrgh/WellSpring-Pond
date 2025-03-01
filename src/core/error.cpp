#include <core/error.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <stdlib.h>

void reportFatalSDLError(const std::string &when) {
    std::cout << "FATAL error occurred " << when << "\nReport: " << SDL_GetError() << "\n";
    SDL_Quit();
    quick_exit(-1); // Error code -1: SDL error
}

void reportNonFatalSDLError(const std::string &when) {
    std::cout << "Error occurred " << when << "\nReport: " << SDL_GetError() << "\n";
}

void reportFatalError(const std::string &error, int code) {
    std::cout << "FATAL error: " << error << "\n";
    SDL_Quit();
    quick_exit(code); // Error code -2: Manual error
}

template<class ...Args> void log(Args... args) {
    std::cout << (... << args) << "\n";
}