#include "Window.h"
#include <SDL3/SDL.h>

enum class AppState {
    Inactive,
    Fail,
    Ok,
};

class App {
public:
    Window window;
    AppState state = AppState::Inactive;
    
    App(int argc, char **argv) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cout << "SDL Failed: " << SDL_GetError() << "\n";
            state = AppState::Fail;
        }

        window = Window(640, 480, "Window", 0);

        state = AppState::Ok;
    }

    AppState verify_state() {
        if (!this) return AppState::Fail;
        // ...
        return state;
    }

    SDL_AppResult process_event(SDL_Event *event) {
        if (event->type == SDL_EVENT_QUIT) {
            // Begins the quitting process
            return SDL_APP_SUCCESS;
        }



        return SDL_APP_CONTINUE;
    }

    SDL_AppResult update() {

        return SDL_APP_CONTINUE;
    }

    void quitting() {

    }
};