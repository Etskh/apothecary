#ifndef _INCLUDE_SDLFONT_HPP
#define _INCLUDE_SDLFONT_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Font.hpp"

class SDLFont: public Font {
public:
    SDLFont (Device* device, const char* fontName);
    virtual ~SDLFont();

private:
    TTF_Font* font;
    SDL_Surface* message;
    SDL_Color color;
};


#endif /* end of include guard: _INCLUDE_SDLFONT_HPP */
