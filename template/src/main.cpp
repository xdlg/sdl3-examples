#include "globals.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static constexpr int WINDOW_WIDTH{800};
static constexpr int WINDOW_HEIGHT{600};

static SDL_Window* window{nullptr};
SDL_Renderer* globals::renderer{nullptr};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
            &globals::renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, 255);
    SDL_RenderClear(globals::renderer);
    SDL_RenderPresent(globals::renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(globals::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
