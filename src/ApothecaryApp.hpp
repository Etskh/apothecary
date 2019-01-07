#ifndef _INCLUDE_APOTHECARYAPP_HPP
#define _INCLUDE_APOTHECARYAPP_HPP

#include "Application.hpp"
#include "scene/SceneNode.hpp"
#include "Device.hpp"
#include "Input.hpp"

class ApothecaryApp: public Application {
public:
    ApothecaryApp();
    virtual ~ApothecaryApp();

    // Lifecycle
    virtual int run();

    // Event hooks
    void onUpdate(event::Type type, event::EventData data);

    // Mutators
    virtual Device::smrtptr getDevice();

private:
    Device::smrtptr device;
    SceneNode scene;
    SceneNode::smrtptr player;
    Input input;
};


#endif /* end of include guard: _INCLUDE_APOTHECARYAPP_HPP */
