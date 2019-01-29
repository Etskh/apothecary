
#include "Texture.hpp"


Logger Texture::logger = Logger("Texture");

Texture::Texture(const char* path)
    : _path(path)
    , _transparency(1.0f)
{
    // empty
}
Texture::~Texture() {
    // empty
}
