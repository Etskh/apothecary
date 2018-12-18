
#include "SDLTexture.hpp"


SDLTexture::SDLTexture(SDL_Texture* texture)
    : Texture()
    , _texture(texture)
{
    logger.info("Texture created");
    if( _texture == nullptr) {
        logger.warn("Texture was initialised will null");
    }
}


SDLTexture::~SDLTexture() {
    if( _texture != nullptr ) {
        logger.info("Texture destroyed");
        SDL_DestroyTexture(_texture);
    }
}
