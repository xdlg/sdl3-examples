#pragma once

#include "texture_wrapper.h"

#include <SDL3/SDL_render.h>

class Streamer {
public:
    Streamer(int width, int height);
    bool init();
    bool render();

private:
    int m_width;
    int m_height;
    textureWrapper::unique_ptr_texture m_texture;
};
