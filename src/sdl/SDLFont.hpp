#ifndef _INCLUDE_SDLFONT_HPP
#define _INCLUDE_SDLFONT_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../core/Logger.hpp"
#include "../Font.hpp"

class SDLFont: public Font {
public:
    SDLFont (SDL_Renderer* renderer, const char* fontName);
    virtual ~SDLFont();

    Texture::smrtptr createTexture(const String& phrase);

private:
    SDL_Renderer* _renderer;
    TTF_Font* font;
    SDL_Surface* message;
    Logger logger;
};


#endif /* end of include guard: _INCLUDE_SDLFONT_HPP */
