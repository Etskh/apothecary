#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributeText.hpp"


ApothecaryApp::ApothecaryApp()
    : Application("The Apothecary")
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

    Font::smrtptr font = device->createFont("./data/OpenSansCondensed-Light.ttf");

    auto title = SceneNode::Create(*this, "title");
    title->get<AttributePosition>()->set(100.f, 100.f, 150.f, 30.0f);
    title->createAttribute<AttributeText>("The Apothecary", font, device);
    scene.addChild(title);

    auto button = SceneNode::Create(*this, "button");
    button->get<AttributePosition>()->set(100.f, 300.f, 150.f, 30.0f);
    button->createAttribute<AttributeText>("Start", font, device);
    scene.addChild(button);

    String debugOutput;
    scene.print_r(debugOutput);
    logger.info(debugOutput);

    return device->run();
}
