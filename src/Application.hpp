#ifndef _INCLUDE_APPLICATION_HPP
#define _INCLUDE_APPLICATION_HPP

#include "Core.hpp"
#include "Device.hpp"

class Application: public event::Dispatcher {
public:
    Application(const char* name);
    virtual ~Application();
    virtual int run() = 0;

    virtual Device::smrtptr getDevice() = 0;

protected:
    DataEntry config;
};



#endif /* end of include guard: _INCLUDE_APPLICATION_HPP */
