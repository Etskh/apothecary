#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributePlayer.hpp"
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

    // Set up the initial keymaps
    // TODO: load from data file
    input.setAxisMap("walk.x", KEY_LEFT, KEY_RIGHT);
    input.setAxisMap("walk.y", KEY_UP, KEY_DOWN);

    input.getAxis("walk.x");

    // Load fonts and initial textures
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

    // Base for all things affected by a camera
    auto world = SceneNode::Create(*this, "world");
    // world->createAttribute<AttributeCamera>()
    scene.addChild(world);

    auto guy = SceneNode::Create(*this, "guy");
    guy->get<AttributePosition>()->set(200.f, 400.f, 20.f, 50.0f);
    guy->createAttribute<AttributePlayer>(&input);
    guy->createAttribute<AttributeImage>(guyTexture, device);
    world->addChild(guy);

    float _speed = 0.f; float _ratio = 0.f; float delta = 0.0016f;
    float deltaMov = _speed * _ratio * delta;
    float deltaX = deltaMov * input.getAxis(String("walk.x"));

    String debugOutput;
    scene.print_r(debugOutput);
    logger.info(debugOutput.c_str());

    return device->run();
}
