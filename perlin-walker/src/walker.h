#pragma once

#include <SDL3/SDL_rect.h>

#include <vector>

class Walker {
public:
    Walker(int windowWidth, int windowHeight);
    void step();
    void render() const;

private:
    int m_windowWidth;
    int m_windowHeight;
    SDL_FPoint m_pos;
    float m_time;
    std::vector<SDL_FPoint> m_trail;
};
