
#include "SDLFont.hpp"


SDLFont::SDLFont(Device* device, const char* fontName)
  : Font(device, fontName)
  , font(nullptr)
{
    font = TTF_OpenFont(fontName, 20);
    if (font == nullptr){
        // log error
    }

    message = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", color);
}

SDLFont::~SDLFont() {
    if( message != nullptr ) {
        SDL_FreeSurface(message);
    }

    if( font != nullptr ) {
        TTF_CloseFont(font);
    }
}
