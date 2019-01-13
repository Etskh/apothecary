#ifndef _INCLUDE_TEXTURE_HPP
#define _INCLUDE_TEXTURE_HPP

#include <memory>

#include "core/String.hpp"
#include "core/Logger.hpp"

class Texture {
public:
    typedef std::shared_ptr<Texture> smrtptr;
    Texture(const char* path);
    virtual ~Texture();

    inline const char* getPath() const { return _path.c_str(); }

protected:
    String _path;
    static Logger logger;
};

#endif /* end of include guard: _INCLUDE_TEXTURE_HPP */
