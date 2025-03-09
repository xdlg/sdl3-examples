#include "globals.h"
#include "splatter.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>

#include <vector>

static constexpr int WINDOW_WIDTH{800};
static constexpr int WINDOW_HEIGHT{600};

static SDL_Window* window{nullptr};
SDL_Renderer* globals::renderer{nullptr};

std::vector<Splatter> splatters;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Splatters", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window,
            &globals::renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    switch (event->type) {
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (event->button.button == SDL_BUTTON_LEFT) {
            Splatter splatter{event->button.x, event->button.y};
            splatters.push_back(splatter);
        } else if (event->button.button == SDL_BUTTON_RIGHT) {
            splatters.clear();
        }
        break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_SetRenderDrawColor(globals::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(globals::renderer);

    for (const auto& splatter : splatters) {
        splatter.render();
    }

    SDL_RenderPresent(globals::renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    SDL_DestroyRenderer(globals::renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
