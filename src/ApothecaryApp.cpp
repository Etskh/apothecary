#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/Scene.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributePlayer.hpp"
#include "scene/AttributeText.hpp"

#include "./Plants.hpp"


ApothecaryApp::ApothecaryApp()
    : Application("The Apothecary")
    , device(nullptr)
    , scene(*this, "root")
    , input(*this)
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

    // Set up all the events
    auto onUpdate = std::bind(&ApothecaryApp::onUpdate, this, std::placeholders::_1, std::placeholders::_2);
    addListener(getName(), event::UPDATE, onUpdate);
    auto onInventoryAdd = std::bind(&ApothecaryApp::onInventoryAdd, this, std::placeholders::_1, std::placeholders::_2);
    addListener(getName(), event::INVENTORY_ADD, onInventoryAdd);

    // Load fonts and initial textures
    Font::smrtptr font = device->createFont("./data/OpenSansCondensed-Light.ttf");
    Texture::smrtptr guyTexture = device->createTexture("./data/character-back.png");

    // Load the ingredientLibrary
    loadIngredients();

    /*
    auto title = SceneNode::Create(*this, "title");
    title->get<AttributePosition>()->set(0.f, 0.f, 150.f, 30.0f);
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
    player->get<AttributePosition>()->set(200.f, 400.f, 50.f, 100.f);
    player->createAttribute<AttributePlayer>(&input);
    player->createAttribute<AttributeImage>(guyTexture, device);
    player->get<AttributeImage>()->setAnchor(ANCHOR_BOT_CENTRE);
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

void ApothecaryApp::onInventoryAdd(event::Type type, event::EventData data) {
    logger.info("Added {} to inventory", data.getString("name"));
    Ingredient plant;

    plant.name = data.getString("name");
    //plant. = data.getNumber("name");

    _ingredients.push_back(plant);
}

Texture::smrtptr ApothecaryApp::loadTexture(const char* path) {
    //_textureLib.find()

    // Load the texture and add it to the list
    Texture::smrtptr texture = device->createTexture(path);
    _textureLib.push_back(texture);

    return texture;
}


void ApothecaryApp::loadIngredients() {
    // TODO: Load the CSV

    //  Load the corresponding image
    // TODO: generate the string path
    Texture::smrtptr texture = loadTexture("./data/dew-herb.png");

    // TODO: For each ingredient, create the ingredient
    Ingredient plant;
    plant.name = "Dew Herb";
    plant.plantType = HERB;
    plant.elementType = EARTH;
    plant.reagentType = NO_REAGENT;
    plant.power = 12.f;
    plant.inventoryTexture = texture;

    // TODO: Load the corresponding image

    // TODO: Add to list of ingredients

    _ingredientLib.push_back(plant);
}


Device::smrtptr ApothecaryApp::getDevice() {
    return device;
}
