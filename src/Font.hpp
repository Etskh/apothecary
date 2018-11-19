#ifndef _INCLUDE_FONT_HPP
#define _INCLUDE_FONT_HPP

#include <memory>

#include "Resource.hpp"
class Device;

class Font: public Resource {
public:
    typedef std::shared_ptr<Font> smrtptr;
public:
    Font (Device* device, const char* fontName);
    virtual ~Font();
};

#endif /* end of include guard: _INCLUDE_FONT_HPP */
