#include "streamer.h"
#include "globals.h"

#include <SDL3/SDL_log.h>

#include <cstring>
#include <stdexcept>
#include <vector>

namespace {
std::vector<uint32_t> pixels;
}

Streamer::Streamer(int width, int height) : m_width{width}, m_height{height}, m_texture{nullptr} {
}

bool Streamer::init() {
    m_texture = textureWrapper::createTexture(globals::renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
    if (!m_texture) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return false;
    }

    pixels.resize(m_width * m_height);

    for (int x{0}; x < m_width; x++) {
        for (int y{0}; y < m_height; y++) {
            const int i{x + y * m_width};
            if (x < m_width / 2 && y < m_height / 2) {
                pixels[i] = 0xff0000ff;
            } else if (x >= m_width / 2 && y < m_height / 2) {
                pixels[i] = 0x00ff00ff;
            } else if (x < m_width / 2 && y >= m_height / 2) {
                pixels[i] = 0x0000ffff;
            } else
                pixels[i] = 0x000000ff;
        }
    }

    return true;
}

bool Streamer::render() {
    if (!m_texture) {
        return false;
    }

    void* pixelsTexture;
    int pitch;

    if (!SDL_LockTexture(m_texture.get(), nullptr, &pixelsTexture, &pitch)) {
        SDL_Log("Couldn't lock texture: %s", SDL_GetError());
        return false;
    }
    std::memcpy(pixelsTexture, pixels.data(), pixels.size() * sizeof(uint32_t));
    SDL_UnlockTexture(m_texture.get());

    SDL_RenderTexture(globals::renderer, m_texture.get(), nullptr, nullptr);

    return true;
}
