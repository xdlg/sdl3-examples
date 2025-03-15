#include "symmetrizer.h"
#include "globals.h"

#include <SDL3/SDL_render.h>

#include <cmath>
#include <numbers>
#include <string>

Symmetrizer::Symmetrizer(int windowWidth, int windowHeight)
    : m_windowWidth{windowWidth}, m_windowHeight{windowHeight},
      m_origin{windowWidth / 2.0f, windowHeight / 2.0f}, m_orderOfSymmetry{2} {
}

void Symmetrizer::handleMouseMotion(SDL_MouseMotionEvent motion) {
    updatePoints(SDL_FPoint{motion.x, motion.y});
}

void Symmetrizer::handleKeyboardEvent(SDL_KeyboardEvent key) {
    const SDL_Keycode keycode = key.key;
    if ((keycode >= SDLK_0) && (keycode <= SDLK_9)) {
        setOrderOfSymmetry(keycode - SDLK_0);
    } else if ((keycode >= SDLK_RIGHT) && (keycode <= SDLK_UP)) {
        moveOrigin(keycode);
    }
}

void Symmetrizer::render() const {
    // Info text
    constexpr float scale{3.0f};
    std::string str{std::to_string(m_orderOfSymmetry)};
    SDL_SetRenderDrawColor(globals::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(globals::renderer, scale, scale);
    SDL_RenderDebugText(globals::renderer, 5, m_windowHeight / scale - 10, str.c_str());
    SDL_SetRenderScale(globals::renderer, 1.0f, 1.0f);

    // Axes
    SDL_SetRenderDrawColor(globals::renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLine(globals::renderer, 0, m_origin.y, m_windowWidth, m_origin.y);
    SDL_RenderLine(globals::renderer, m_origin.x, 0, m_origin.x, m_windowHeight);

    // Points
    SDL_SetRenderDrawColor(globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    for (const auto& point : m_points) {
        constexpr float SIZE{20.0f};
        SDL_FRect rect{point.x - SIZE / 2, point.y - SIZE / 2, SIZE, SIZE};
        SDL_RenderFillRect(globals::renderer, &rect);
    }
}

void Symmetrizer::updatePoints(SDL_FPoint mainPoint) {
    m_points.clear();

    for (int i{0}; i < m_orderOfSymmetry; i++) {
        const auto w{m_windowWidth};
        const auto h{m_windowHeight};
        const auto x{mainPoint.x};
        const auto y{mainPoint.y};

        // See readme for demonstration
        float beta{static_cast<float>(2 * std::numbers::pi * i / m_orderOfSymmetry)};
        float x_sym{static_cast<float>(
            (x - m_origin.x) * std::cos(beta) + (y - m_origin.y) * std::sin(beta) + m_origin.x)};
        float y_sym{static_cast<float>(
            (y - m_origin.y) * std::cos(beta) - (x - m_origin.x) * std::sin(beta) + m_origin.y)};

        if ((x_sym >= 0) && (x_sym < w) && (y_sym >= 0) && (y_sym < h)) {
            m_points.emplace_back(x_sym, y_sym);
        }
    }
}

void Symmetrizer::setOrderOfSymmetry(unsigned int s) {
    m_orderOfSymmetry = s;
    if (!m_points.empty()) {
        updatePoints(m_points[0]);
    }
}

void Symmetrizer::moveOrigin(SDL_Keycode keycode) {
    constexpr float ORIGIN_INCREMENT{10.0f};
    SDL_FPoint newOrigin{m_origin};

    switch (keycode) {
    case SDLK_RIGHT:
        newOrigin.x += ORIGIN_INCREMENT;
        break;
    case SDLK_LEFT:
        newOrigin.x -= ORIGIN_INCREMENT;
        break;
    case SDLK_DOWN:
        newOrigin.y += ORIGIN_INCREMENT;
        break;
    case SDLK_UP:
        newOrigin.y -= ORIGIN_INCREMENT;
        break;
    }

    if ((newOrigin.x >= 0) && (newOrigin.x <= m_windowWidth) && (newOrigin.y >= 0)
        && (newOrigin.y <= m_windowHeight)) {
        m_origin = newOrigin;
    }

    if (!m_points.empty()) {
        updatePoints(m_points[0]);
    }
}
