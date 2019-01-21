
#include "AttributePlant.hpp"
#include "AttributeImage.hpp"

AttributeType AttributePlant::type = ATTRIBUTETYPE_PLANT;

AttributePlant::AttributePlant(Application* app, Ingredient ingredient)
    : AttributeInteractive(app)
    , _app(app)
    , _ingredient(ingredient)
    , _isActive(true)
{
    // empty
}

AttributePlant::~AttributePlant() {
    // empty
}

// For catching the event
void AttributePlant::onActivate(event::EventData data) {
    if( _isActive ) {
        auto imageAttr = getSibling<AttributeImage>();
        imageAttr->hide();

        // Then move the ingredient to the inventory
        event::EventData inventoryEvent;
        inventoryEvent.setString("name", _ingredient.name.c_str());
        _app->send(event::INVENTORY_ADD, inventoryEvent);

        _isActive = false;
    }
}
