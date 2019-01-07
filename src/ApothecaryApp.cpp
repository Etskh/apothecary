#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/Scene.hpp"
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
    input.setButtonMap("interact", KEY_SPACE);

    auto onUpdate = std::bind(&ApothecaryApp::onUpdate, this, std::placeholders::_1, std::placeholders::_2);
    addListener(getName(), event::UPDATE, onUpdate);


    // Load fonts and initial textures
    Font::smrtptr font = device->createFont("./data/OpenSansCondensed-Light.ttf");
    Texture::smrtptr guyTexture = device->createTexture("./data/character-back.png");
    Texture::smrtptr bgTexture = device->createTexture("./data/background.png");

    /*
    auto title = SceneNode::Create(*this, "title");
    title->get<AttributePosition>()->set(100.f, 100.f, 150.f, 30.0f);
    title->createAttribute<AttributeText>("The Apothecary", font, device);
    scene.addChild(title);

    auto button = SceneNode::Create(*this, "button");
    button->createAttribute<AttributeText>("Start", font, device);
    button->get<AttributePosition>()->set(0.f, 200.f, 90.f, 30.f);
    scene.addChild(button);
    */
    // Base for all things affected by a camera
    auto world = SceneNode::Create(*this, "world");
    // world->createAttribute<AttributeCamera>()
    scene.addChild(world);

    world->addChild(LoadScene(*this, "./data/scene1.json"));

    player = SceneNode::Create(*this, "guy");
    player->get<AttributePosition>()->set(200.f, 400.f, 32.f, 64.f);
    player->createAttribute<AttributePlayer>(&input);
    player->createAttribute<AttributeImage>(guyTexture, device);
    world->addChild(player);

    // Debug printing here
    {
        String debugOutput;
        //scene.print_r(debugOutput);
        //logger.info(debugOutput.c_str());

        input.print_r(debugOutput);
        logger.info(debugOutput.c_str());
    }

    return device->run();
}

void ApothecaryApp::onUpdate(event::Type type, event::EventData data) {

    // If the player hit the "interact button"
    if( input.getButton("interact") ) {
        float x = player->get<AttributePosition>()->getX();
        float y = player->get<AttributePosition>()->getY();

        event::EventData interactEvent;
        interactEvent.setNumber("x", x);
        interactEvent.setNumber("y", y);

        send(event::APP_INTERACT, interactEvent);
    }
}


Device::smrtptr ApothecaryApp::getDevice() {
    return device;
}
