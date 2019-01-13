#ifndef _INCLUDE_APOTHECARYAPP_HPP
#define _INCLUDE_APOTHECARYAPP_HPP

#include <vector>
#include <list>

#include "Application.hpp"
#include "scene/SceneNode.hpp"
#include "Device.hpp"
#include "Input.hpp"
#include "Plants.hpp"

class ApothecaryApp: public Application {
public:
    ApothecaryApp();
    virtual ~ApothecaryApp();

    // Lifecycle
    virtual int run();
    void loadIngredients();

    // Event hooks
    void onUpdate(event::Type type, event::EventData data);
    void onInventoryAdd(event::Type type, event::EventData data);

    // Resources
    Texture::smrtptr loadTexture(const char* path);

    // Mutators
    virtual Device::smrtptr getDevice();

private:
    std::vector<Ingredient> _ingredientLib;
    std::vector<Texture::smrtptr> _textureLib;
    Device::smrtptr device;
    SceneNode scene;
    SceneNode::smrtptr player;
    std::list<Ingredient> _ingredients;
    Input input;
};


#endif /* end of include guard: _INCLUDE_APOTHECARYAPP_HPP */
