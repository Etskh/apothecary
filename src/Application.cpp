
#include <SDL2/SDL.h>

#include "Application.hpp"
#include "sdl/SDLDevice.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributeText.hpp"

Application::Application(const char* name)
  : logger(name)
  , device(nullptr)
  , scene("root")
{
    config.setString("application title", "The Apothecary");
    config.setNumber("application width", 640);
    config.setNumber("application height", 480);
}

Application::~Application() {
    // empty
}

int Application::run() {
    device = Device::smrtptr(new SDLDevice());
    if( !device->init(config)) {
        logger.error("Quitting because device could not be created");
        return 1;
    }

    Font::smrtptr font = device->createFont("./data/OpenSansCondensed-Light.ttf");

    auto title = SceneNode::Create("title");
    title->get<AttributePosition>()->set(100.f, 100.f, 150.f, 30.0f);
    title->createAttribute<AttributeText>("The Apothecary", font, device);
    scene.addChild(title);

    auto button = SceneNode::Create("button");
    button->get<AttributePosition>()->set(100.f, 300.f, 150.f, 30.0f);
    button->createAttribute<AttributeText>("Start", font, device);
    scene.addChild(button);

    String debugOutput;
    scene.print_r(debugOutput);
    logger.info(debugOutput);

    return device->run();
}
