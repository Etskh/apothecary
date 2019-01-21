#include "ApothecaryApp.hpp"

#include "sdl/SDLDevice.hpp"
#include "scene/Scene.hpp"
#include "scene/AttributePosition.hpp"
#include "scene/AttributeImage.hpp"
#include "scene/AttributePlayer.hpp"
#include "scene/AttributePlant.hpp"
#include "scene/AttributeText.hpp"

#include "./Plants.hpp"


ApothecaryApp::ApothecaryApp()
    : Application("The Apothecary")
    , device(nullptr)
    , input(*this)
    , _scene(*this, "root")
    , _gameState(GAMESTATE_WORLD)
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

    device->setIcon("./data/dew-herb.png");

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
    _scene.addChild(world);

    auto deco1 = SceneNode::Create(*this, "deco1");
    deco1->get<AttributePosition>()->set(200, 200, 128, 128);
    deco1->createAttribute<AttributeImage>(loadTexture("./data/grass-patch.png"), device);
    world->addChild(deco1);
    auto deco2 = SceneNode::Create(*this, "deco2");
    deco2->get<AttributePosition>()->set(120, 230, 128, 128);
    deco2->createAttribute<AttributeImage>(loadTexture("./data/grass-patch.png"), device);
    world->addChild(deco2);
    auto deco3 = SceneNode::Create(*this, "deco3");
    deco3->get<AttributePosition>()->set(0, 300, 128, 128);
    deco3->createAttribute<AttributeImage>(loadTexture("./data/grass-patch.png"), device);
    world->addChild(deco3);

    // TODO: load scene with file
    world->addChild(createPlant("Dew Herb", 200.f, 200.f));
    world->addChild(createPlant("Ember Flower", 130.f, 300.f));
    world->addChild(createPlant("Dew Herb", 100.f, 400.f));
    world->addChild(createPlant("Dew Herb", 300.f, 250.f));
    world->addChild(createPlant("Ember Flower", 240.f, 10.f));
    world->addChild(createPlant("Ember Flower", 150.f, 320.f));
    world->addChild(createPlant("Indigo Reed", 220.f, 280.f));

    _player = SceneNode::Create(*this, "guy");
    _player->get<AttributePosition>()->set(200.f, 400.f, 50.f, 100.f);
    _player->createAttribute<AttributePlayer>(&input);
    _player->createAttribute<AttributeImage>(guyTexture, device);
    _player->get<AttributeImage>()->setAnchor(ANCHOR_BOT_CENTRE);
    world->addChild(_player);

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

    float playerX = _player->get<AttributePosition>()->getX();
    float playerY = _player->get<AttributePosition>()->getY();

    if(_gameState == GAMESTATE_WORLD ) {
        // If the player hit the "interact button"
        if( input.getButton("interact") ) {
            event::EventData interactEvent;
            interactEvent.setNumber("x", playerX);
            interactEvent.setNumber("y", playerY);

            send(event::APP_INTERACT, interactEvent);
        }

        // Move camera to player if we're walking around
        // Get the screen size
        float screenX = 640;
        float screenY = 480;
        device->getCamera().moveTo(
            Vector2((screenX / 2) - playerX, (screenY / 2) - playerY + 64)
        );
    }
}

void ApothecaryApp::onInventoryAdd(event::Type type, event::EventData data) {
    logger.info("Added {} to inventory", data.getString("name"));
    Ingredient plant;

    plant.name = data.getString("name");
    //plant. = data.getNumber("name");

    _inventory.push_back(plant);
}

Texture::smrtptr ApothecaryApp::loadTexture(const char* path) {
    Texture::smrtptr texture = Texture::smrtptr(nullptr);

    // Grab the texture from the list
    try {
        texture = _textureLib.at(path);
    } catch( std::out_of_range exception) {
        texture = device->createTexture(path);
        // TODO: put the ./data/ on the front of it
        _textureLib.insert(std::pair<String,Texture::smrtptr>(path, texture));
    }
    return texture;
}


SceneNode::smrtptr ApothecaryApp::createPlant(const char* type, float x, float y) {
    Ingredient plant;
    try {
        plant = _ingredientLib.at(type);
    } catch( std::out_of_range exception) {
        logger.error("No plant named {}", type);
        return SceneNode::smrtptr(nullptr);
    }

    auto grass = SceneNode::Create(*this, stringify(createGuid()));

    grass->get<AttributePosition>()->set(x, y, 32, 32 * plant.height);
    grass->createAttribute<AttributeImage>(plant.inventoryTexture, device);
    grass->get<AttributeImage>()->setAnchor(ANCHOR_BOT_CENTRE);
    grass->createAttribute<AttributePlant>(this, plant);

    return grass;
}


void ApothecaryApp::loadIngredients() {
    // TODO: Load the CSV

    // TODO: For each ingredient, create the ingredient
    Ingredient plant;

    // TODO: loop over the ingredients

    plant.name = "Dew Herb";
    plant.plantType = HERB;
    plant.elementType = EARTH;
    plant.reagentType = NO_REAGENT;
    plant.power = 12.f;
    plant.height = 1.f;
    plant.weight = 0.5f;
    plant.inventoryTexture = loadTexture("./data/dew-herb.png");
    _ingredientLib.insert(std::pair<String, Ingredient>(plant.name, plant));

    plant.name = "Ember Flower";
    plant.plantType = FLOWER;
    plant.elementType = FIRE;
    plant.reagentType = NO_REAGENT;
    plant.power = 5.f;
    plant.height = 2.f;
    plant.weight = 0.5f;
    plant.inventoryTexture = loadTexture("./data/ember-flower.png");
    _ingredientLib.insert(std::pair<String, Ingredient>(plant.name, plant));

    plant.name = "Indigo Reed";
    plant.plantType = REED;
    plant.elementType = NO_ELEMENT;
    plant.reagentType = REAGENT_CATALYST;
    plant.power = 7.f;
    plant.height = 2.f;
    plant.weight = 0.5f;
    plant.inventoryTexture = loadTexture("./data/indigo-reed.png");
    _ingredientLib.insert(std::pair<String, Ingredient>(plant.name, plant));
}


Device::smrtptr ApothecaryApp::getDevice() {
    return device;
}
