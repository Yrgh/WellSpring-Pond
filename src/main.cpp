#include <SDL2/SDL.h>
#include <iostream>

#include "Window.h"

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL Failed!\n" << SDL_GetError();
        return 1;
    }

    Window window(640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, "Window", 0);
    
    return 0;
}