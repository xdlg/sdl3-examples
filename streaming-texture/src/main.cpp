#include "globals.h"
#include "streamer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cstring>
#include <vector>

static constexpr int WINDOW_WIDTH{800};
static constexpr int WINDOW_HEIGHT{600};

static SDL_Window* window{nullptr};
SDL_Renderer* globals::renderer{nullptr};
static Streamer streamer{WINDOW_WIDTH, WINDOW_HEIGHT};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Streaming Texture", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
            &globals::renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!streamer.init()) {
        SDL_Log("Couldn't initialize streamer");
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
    streamer.render();
    SDL_RenderPresent(globals::renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(globals::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
