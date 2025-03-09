#include "splatter.h"
#include "globals.h"

#include <SDL3/SDL_pixels.h>

#include <random>

namespace {
std::mt19937 generator{std::random_device{}()};
}

Splatter::Splatter(float x_center, float y_center) {
    static constexpr int N_POINTS_MIN{100};
    static constexpr int N_POINTS_MAX{1000};
    static constexpr float STANDARD_DEV_MIN{1.0};
    static constexpr float STANDARD_DEV_MAX{20.0};
    static constexpr int RGB_COLOR_MIN{0};
    static constexpr int RGB_COLOR_MAX{255};

    std::uniform_int_distribution<> n_points_dis{N_POINTS_MIN, N_POINTS_MAX};
    std::uniform_real_distribution<> standard_dev_dis{STANDARD_DEV_MIN, STANDARD_DEV_MAX};
    std::uniform_int_distribution<> color_dis{RGB_COLOR_MIN, RGB_COLOR_MAX};

    const auto n_points{n_points_dis(generator)};
    const auto standard_dev{standard_dev_dis(generator)};

    const auto r{static_cast<uint8_t>(color_dis(generator))};
    const auto g{static_cast<uint8_t>(color_dis(generator))};
    const auto b{static_cast<uint8_t>(color_dis(generator))};
    m_color = {r, g, b, SDL_ALPHA_OPAQUE};

    std::normal_distribution<> x_dis{x_center, standard_dev};
    std::normal_distribution<> y_dis{y_center, standard_dev};

    for (int i{0}; i < n_points; i++) {
        const auto x{static_cast<float>(x_dis(generator))};
        const auto y{static_cast<float>(y_dis(generator))};
        SDL_FPoint point{x, y};
        m_points.push_back(point);
    }
}

void Splatter::render() const {
    SDL_SetRenderDrawColor(globals::renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderPoints(globals::renderer, m_points.data(), m_points.size());
}
