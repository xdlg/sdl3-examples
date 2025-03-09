#include "globals.h"
#include "walker.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_timer.h>

static constexpr int WINDOW_WIDTH{800};
static constexpr int WINDOW_HEIGHT{600};

static SDL_Window* window{nullptr};
SDL_Renderer* globals::renderer{nullptr};

Walker walker{WINDOW_WIDTH, WINDOW_HEIGHT};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Perlin Walker", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
            &globals::renderer)) {
        SDL_Log("Couldn't create window and globals::renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
        break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(globals::renderer);

    walker.step();
    walker.render();

    SDL_RenderPresent(globals::renderer);

    SDL_Delay(30);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(globals::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
