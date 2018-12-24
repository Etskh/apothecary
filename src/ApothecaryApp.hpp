#ifndef _INCLUDE_APOTHECARYAPP_HPP
#define _INCLUDE_APOTHECARYAPP_HPP

#include "Application.hpp"
#include "scene/SceneNode.hpp"
#include "Device.hpp"

class ApothecaryApp: public Application {
public:
    ApothecaryApp();
    virtual ~ApothecaryApp();

    virtual int run();

private:
    Device::smrtptr device;
    SceneNode scene;
};


#endif /* end of include guard: _INCLUDE_APOTHECARYAPP_HPP */
