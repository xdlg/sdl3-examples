#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <vector>

class Splatter {
public:
    Splatter(float x_center, float y_center);
    void render() const;

private:
    SDL_Color m_color;
    std::vector<SDL_FPoint> m_points;
};
