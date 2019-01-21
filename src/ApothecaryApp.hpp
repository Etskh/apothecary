#ifndef _INCLUDE_APOTHECARYAPP_HPP
#define _INCLUDE_APOTHECARYAPP_HPP

#include <map>
#include <list>

#include "Application.hpp"
#include "scene/SceneNode.hpp"
#include "Device.hpp"
#include "Input.hpp"
#include "Plants.hpp"


enum GameState {
    GAMESTATE_WORLD,
    GAMESTATE_INVENTORY,
};


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
    SceneNode::smrtptr createPlant(const char* type, float x, float y);

    // Mutators
    virtual Device::smrtptr getDevice();

private:
    // Systems
    Device::smrtptr device;
    Input input;

    // Resources
    std::map<String, Ingredient> _ingredientLib;
    std::map<String, Texture::smrtptr> _textureLib;

    // Gameplay
    SceneNode _scene;
    SceneNode::smrtptr _player;
    std::list<Ingredient> _inventory;
    GameState _gameState;
};


#endif /* end of include guard: _INCLUDE_APOTHECARYAPP_HPP */
