#ifndef _INCLUDE_TEXTURE_HPP
#define _INCLUDE_TEXTURE_HPP

#include <memory>

#include "core/Logger.hpp"

class Texture {
public:
    typedef std::shared_ptr<Texture> smrtptr;
    Texture();
    virtual ~Texture();

protected:
    static Logger logger;
};

#endif /* end of include guard: _INCLUDE_TEXTURE_HPP */
