#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_rect.h>

#include <vector>

class Symmetrizer {
public:
    Symmetrizer(int windowWidth, int windowHeight);
    void handleMouseMotion(SDL_MouseMotionEvent motion);
    void handleKeyboardEvent(SDL_KeyboardEvent key);
    void render() const;

private:
    int m_windowWidth;
    int m_windowHeight;
    unsigned int m_orderOfSymmetry;
    SDL_FPoint m_origin;
    std::vector<SDL_FPoint> m_points;

    void updatePoints(SDL_FPoint mainPoint);
    void setOrderOfSymmetry(unsigned int s);
    void moveOrigin(SDL_Keycode keycode);
};
