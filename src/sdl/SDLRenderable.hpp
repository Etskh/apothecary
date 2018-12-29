#ifndef _INCLUDE_SDLRENDERABLE_HPP
#define _INCLUDE_SDLRENDERABLE_HPP

#include <memory>

#include "SDLTexture.hpp"

struct SDLRenderable {
    std::shared_ptr<SDLTexture> texture;
    // absolute values
    int posX;
    int posY;
    int width;
    int height;

    SDLRenderable(Texture::smrtptr tex, int x, int y, int w, int h);
};


#endif /* end of include guard: _INCLUDE_SDLRENDERABLE_HPP */
