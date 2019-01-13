
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributeText.hpp"
#include "scene/AttributePlant.hpp"
#include "Plants.hpp"




SceneNode::smrtptr CreatePlant(Application& app, const char* name, float x, float y) {
    auto grass = SceneNode::Create(app, stringify(createGuid()));

    Device::smrtptr device = app.getDevice();
    Texture::smrtptr herbTexture = device->createTexture("./data/ember-flower.png");

    Ingredient plant;
    plant.name = "Dew Herb";
    plant.plantType = HERB;
    plant.elementType = EARTH;
    plant.reagentType = NO_REAGENT;
    plant.power = 12.f;
    plant.inventoryTexture = herbTexture;

    grass->get<AttributePosition>()->set(x, y, 32, 32);
    grass->createAttribute<AttributeImage>(herbTexture, device);
    grass->get<AttributeImage>()->setAnchor(ANCHOR_BOT_CENTRE);
    grass->createAttribute<AttributePlant>(&app, plant);

    return grass;
}
