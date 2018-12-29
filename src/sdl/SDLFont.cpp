
#include "SDLFont.hpp"
#include "SDLTexture.hpp"

SDLFont::SDLFont(SDL_Renderer* renderer, const char* fontName)
  : Font(fontName)
  , _renderer(renderer)
  , font(nullptr)
  , message(nullptr)
  , logger(String("SDLFont:") + fontName)
{
    font = TTF_OpenFont(fontName, 32);
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
    SDL_Color White = {255, 255, 255};

    if( font == nullptr ) {
        logger.error("Attempting to create texture from blank font");
        return Texture::smrtptr(nullptr);
    }

    // Create the surface for the message
    if( message != nullptr ) {
        SDL_FreeSurface(message);
    }
    message = TTF_RenderText_Solid(font, phrase.c_str(), White);
    if( message == nullptr ) {
        logger.error("Couldnt create a SDL_Surface* from TTF_RenderText_Solid");
        return Texture::smrtptr(nullptr);
    }

    // Create the texture out of the surface
    SDL_Texture* textMessage = SDL_CreateTextureFromSurface(_renderer, message);
    auto texture = Texture::smrtptr(new SDLTexture(textMessage));

    return texture;
}
