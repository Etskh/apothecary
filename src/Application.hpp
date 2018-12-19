#ifndef _INCLUDE_APPLICATION_HPP
#define _INCLUDE_APPLICATION_HPP

#include "Core.hpp"
#include "scene/SceneNode.hpp"

#include "Device.hpp"
/*
struct GameState {
    float timeOfDay;
    float gold;
    struct Factions {
        float assassins;
        float paladins;
        float mercenaries;
        float theThrone;
    } factions;
};
*/

class Application {
public:
    Application(const char* name);
    virtual ~Application();
    int run();

private:
    Logger logger;
    Device::smrtptr device;
    //
    // GameState state;
    DataEntry config;
    //
    SceneNode scene;
};



#endif /* end of include guard: _INCLUDE_APPLICATION_HPP */
