#ifndef _INCLUDE_PLANTS_HPP
#define _INCLUDE_PLANTS_HPP

#include "./Texture.hpp"
#include "scene/SceneNode.hpp"

enum PlantType {
    NO_PLANT,
    FLOWER,
    HERB,
    FERN,
    REED,
    MUSHROOM,
    VINE,
    PLANT_COUNT,
};

enum ElementType {
    NO_ELEMENT,
    LIGHT,
    DARKNESS,
    FIRE,
    COLD,
    EARTH,
    AETHER,
    ELEMENT_COUNT,
};

enum ReagentType {
    NO_REAGENT,
    REAGENT_CATALYST,
    REAGENT_ESSENCE,
    REAGENT_ELEMENT,
    REAGENT_TYPE_COUNT,
};

enum InventoryType {
    NO_INVENTORY,
    INGREDIENT,
    REAGENT,
    ELEMENT,
    INVENTORY_TYPE_COUNT,
};

struct Ingredient {
    String name;
    PlantType plantType;
    ElementType elementType;
    ReagentType reagentType;
    float level;
    float power;
    InventoryType inventoryType;
    Texture::smrtptr inventoryTexture;
};



SceneNode::smrtptr CreatePlant(Application& app, const char* name, float x, float y);


#endif /* end of include guard: _INCLUDE_PLANTS_HPP */
