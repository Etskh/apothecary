#ifndef _INCLUDE_DEVICE_HPP
#define _INCLUDE_DEVICE_HPP

#include <memory>

#include "DataEntry.hpp"
#include "Font.hpp"

class Device {
public:
    typedef std::shared_ptr<Device> smrtptr;
    virtual ~Device();
public:
    virtual bool init(const DataEntry& config) = 0;
    virtual void render(float delta) = 0;

    virtual Font::smrtptr createFont(const char* fontName) = 0;

protected:
    Device();
};


#endif /* end of include guard: _INCLUDE_DEVICE_HPP */
