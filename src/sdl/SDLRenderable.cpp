
#include "SDLRenderable.hpp"

SDLRenderable::SDLRenderable(Texture::smrtptr tex, int x, int y, int w, int h)
 : texture(std::dynamic_pointer_cast<SDLTexture>(tex))
 , posX(x)
 , posY(y)
 , width(w)
 , height(h)
 , transparency(1.0f)
 , isWorldSpace(true)
{
    // empty
}
