#ifndef _INCLUDE_FONT_HPP
#define _INCLUDE_FONT_HPP

#include <memory>

#include "Texture.hpp"
#include "Resource.hpp"

class Font: public Resource {
public:
    typedef std::shared_ptr<Font> smrtptr;
public:
    Font (const char* fontName);
    virtual ~Font();

    virtual Texture::smrtptr createTexture(const String& phrase) = 0;
};

#endif /* end of include guard: _INCLUDE_FONT_HPP */
