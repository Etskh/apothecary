
#include "SDLRenderable.hpp"

SDLRenderable::SDLRenderable(Texture::smrtptr tex, int x, int y, int w, int h)
 : texture(std::dynamic_pointer_cast<SDLTexture>(tex))
 , xPos(x)
 , yPos(y)
 , width(w)
 , height(h)
{
    // empty
}
