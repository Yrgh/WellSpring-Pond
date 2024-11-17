#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

#include "App.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    App *app = new App(argc, argv);
    if (app->state == AppState::Fail) return SDL_APP_FAILURE;
    *appstate = (void *) app;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    App *app = (App *) appstate;
    if (app->verify_state() == AppState::Fail) return SDL_APP_FAILURE;
    return app->process_event(event);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    App *app = (App *) appstate;
    if (app->verify_state() == AppState::Fail) return SDL_APP_FAILURE;
    return app->update();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    App *app = (App *) appstate;
    if (app->verify_state() == AppState::Fail) return;
    app->quitting();
}