
#include "Texture.hpp"


Logger Texture::logger = Logger("Texture");

Texture::Texture(const char* path)
    : _path(path)
{
    // empty
}
Texture::~Texture() {
    // empty
}
