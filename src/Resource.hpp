#ifndef _INCLUDE_RESOURCE_HPP
#define _INCLUDE_RESOURCE_HPP

#include "core/String.hpp"

class Resource {
public:
    Resource(const char* name);
    //Resource(Device* device);
    virtual ~Resource();

    inline const String& getName() const {
        return resourceName;
    }

private:
    //Device* device;
    String resourceName;
};

#endif /* end of include guard: _INCLUDE_RESOURCE_HPP */
