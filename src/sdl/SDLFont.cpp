
#include "SDLFont.hpp"
#include "SDLTexture.hpp"

SDLFont::SDLFont(SDL_Renderer* renderer, const char* fontName)
  : Font(fontName)
  , _renderer(renderer)
  , font(nullptr)
  , logger(String("SDLFont:") + fontName)
{
    font = TTF_OpenFont(fontName, 24);
    if (font == nullptr){
        logger.error(String("Could not open file") + getName());
    }
}

SDLFont::~SDLFont() {
    if( message != nullptr ) {
        SDL_FreeSurface(message);
    }

    if( font != nullptr ) {
        TTF_CloseFont(font);
    }
}

Texture::smrtptr SDLFont::createTexture(const String& phrase) {
    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    // Create the surface for the message
    if( message != nullptr ) {
        SDL_FreeSurface(message);
    }
    message = TTF_RenderText_Solid(font,  phrase.c_str(), White);

    // Create the texture out of the surface
    SDL_Texture* textMessage = SDL_CreateTextureFromSurface(_renderer, message);
    auto texture = Texture::smrtptr(new SDLTexture(textMessage));

    return texture;
}
