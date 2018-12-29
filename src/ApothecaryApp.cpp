#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributeText.hpp"


ApothecaryApp::ApothecaryApp()
    : Application("The Apothecary")
    , input(*this)
    , device(nullptr)
    , scene(*this, "root")
{
    // empty
}

ApothecaryApp::~ApothecaryApp() {
    // empty
}

int ApothecaryApp::run() {
    device = Device::smrtptr(new SDLDevice(*this));
    if( !device->init(config)) {
        logger.error("Quitting because device could not be created");
        return 1;
    }

    input.setAxisMap("walk.x", KEY_LEFT, KEY_RIGHT);
    input.setAxisMap("walk.y", KEY_UP, KEY_DOWN);

    Font::smrtptr font = device->createFont("./data/OpenSansCondensed-Light.ttf");
    Texture::smrtptr guyTexture = device->createTexture("./data/sprite.png");

    auto title = SceneNode::Create(*this, "title");
    title->get<AttributePosition>()->set(100.f, 100.f, 150.f, 30.0f);
    title->createAttribute<AttributeText>("The Apothecary", font, device);
    scene.addChild(title);

    auto button = SceneNode::Create(*this, "button");
    button->createAttribute<AttributeText>("Start", font, device);
    button->get<AttributePosition>()->set(0.f, 200.f, 90.f, 30.f);
    scene.addChild(button);

    auto world = SceneNode::Create(*this, "world");
    scene.addChild(world);

    auto guy = SceneNode::Create(*this, "guy");
    guy->get<AttributePosition>()->set(200.f, 400.f, 20.f, 50.0f);
    guy->createAttribute<AttributeImage>(guyTexture, device);
    world->addChild(guy);

    String debugOutput;
    scene.print_r(debugOutput);
    logger.info(debugOutput);

    return device->run();
}
