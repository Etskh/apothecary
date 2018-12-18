#ifndef _INCLUDE_SDLTEXTURE_HPP
#define _INCLUDE_SDLTEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../Texture.hpp"

class SDLTexture: public Texture {
public:
    SDLTexture(SDL_Texture* texture);
    virtual ~SDLTexture();

    inline SDL_Texture* getHandle() const { return _texture; }

private:
    SDL_Texture* _texture;
};

#endif /* end of include guard: _INCLUDE_SDLTEXTURE_HPP */
