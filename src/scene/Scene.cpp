
// #include "extern/rapidjson/rapidjson.h"
#include "Scene.hpp"
#include "AttributePosition.hpp"
#include "AttributeImage.hpp"
#include "AttributeText.hpp"
#include "AttributeInteractive.hpp"


SceneNode::smrtptr LoadScene(Application& app, const String& name) {

    Device::smrtptr device = app.getDevice();
    Texture::smrtptr herbTexture = device->createTexture("./data/dew-herb.png");
    Texture::smrtptr reedTexture = device->createTexture("./data/indigo-reed.png");
    SceneNode::smrtptr world = SceneNode::Create(app, name);

    auto deco = SceneNode::Create(app, "deco");
    deco->get<AttributePosition>()->set(0, 0, 32, 32);

    auto grass = SceneNode::Create(app, "grass_1");
    grass->get<AttributePosition>()->set(378, 128, 32, 32);
    grass->createAttribute<AttributeImage>(herbTexture, device);
    grass->createAttribute<AttributeInteractive>(&app);
    deco->addChild(grass);

    auto grass2 = SceneNode::Create(app, "grass_2");
    grass2->get<AttributePosition>()->set(258, 320, 32, 32);
    grass2->createAttribute<AttributeImage>(herbTexture, device);
    grass2->createAttribute<AttributeInteractive>(&app);
    deco->addChild(grass2);

    auto grass3 = SceneNode::Create(app, "grass_3");
    grass3->get<AttributePosition>()->set(342, 18, 32, 32);
    grass3->createAttribute<AttributeImage>(herbTexture, device);
    grass3->createAttribute<AttributeInteractive>(&app);
    deco->addChild(grass3);

    auto reed1 = SceneNode::Create(app, "reed_1");
    reed1->get<AttributePosition>()->set(322, 245, 32, 64);
    reed1->createAttribute<AttributeImage>(reedTexture, device);
    reed1->createAttribute<AttributeInteractive>(&app);
    deco->addChild(reed1);

    auto reed2 = SceneNode::Create(app, "reed_2");
    reed2->get<AttributePosition>()->set(120, 90, 32, 64);
    reed2->createAttribute<AttributeImage>(reedTexture, device);
    reed2->createAttribute<AttributeInteractive>(&app);
    deco->addChild(reed2);

    world->addChild(deco);

    return world;
}
