#include "walker.h"

#include "PerlinNoise.hpp"
#include "globals.h"

#include <SDL3/SDL_pixels.h>

#include <random>

namespace {
constexpr float WALKER_WIDTH{20.0f};
constexpr float WALKER_HEIGHT{20.0f};

const siv::PerlinNoise::seed_type seed{std::random_device{}()};
const siv::PerlinNoise perlin{seed};
} // namespace

Walker::Walker(int windowWidth, int windowHeight)
    : m_windowWidth{windowWidth}, m_windowHeight{windowHeight}, m_pos{SDL_FPoint{0.0f, 0.0f}},
      m_time{0.0f} {
}

void Walker::step() {
    static constexpr float TIME_OFFSET{1000.0f};
    static constexpr float TIME_INCREMENT{0.01f};

    m_pos.x = perlin.noise1D_01(m_time) * m_windowWidth;
    m_pos.y = perlin.noise1D_01(m_time + TIME_OFFSET) * m_windowHeight;

    const float xCenterWalker{m_pos.x + (WALKER_WIDTH / 2.0f)};
    const float yCenterWalker{m_pos.y + (WALKER_HEIGHT / 2.0f)};
    m_trail.emplace_back(xCenterWalker, yCenterWalker);

    m_time += TIME_INCREMENT;
}

void Walker::render() const {
    constexpr SDL_Color WALKER_COLOR{128, 0, 128, SDL_ALPHA_OPAQUE};
    constexpr SDL_Color TRAIL_COLOR{173, 92, 173, SDL_ALPHA_OPAQUE};

    SDL_SetRenderDrawColor(globals::renderer, TRAIL_COLOR.r, TRAIL_COLOR.g, TRAIL_COLOR.b,
        TRAIL_COLOR.a);
    SDL_RenderPoints(globals::renderer, m_trail.data(), m_trail.size());

    SDL_FRect rect{m_pos.x, m_pos.y, WALKER_WIDTH, WALKER_HEIGHT};
    SDL_SetRenderDrawColor(globals::renderer, WALKER_COLOR.r, WALKER_COLOR.g, WALKER_COLOR.b,
        WALKER_COLOR.a);
    SDL_RenderFillRect(globals::renderer, &rect);
}
