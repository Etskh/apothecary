#ifndef _INCLUDE_SDLTEXTURE_HPP
#define _INCLUDE_SDLTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Texture.hpp"

class SDLTexture: public Texture {
public:

private:
    SDL_Texture* texture;
    SDL_Surface* surface;
};

#endif /* end of include guard: _INCLUDE_SDLTEXTURE_HPP */
