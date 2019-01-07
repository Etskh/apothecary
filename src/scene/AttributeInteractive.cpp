
#include <cstdio>

#include "AttributeImage.hpp"
#include "AttributeInteractive.hpp"

AttributeType AttributeInteractive::type = ATTRIBUTETYPE_INTERACTIVE;

AttributeInteractive::AttributeInteractive(Application* app)
    : Attribute(AttributeInteractive::type)
    , _id(createGuid())
{
    auto onInteract = std::bind(&AttributeInteractive::onInteract, this, std::placeholders::_1, std::placeholders::_2);
    app->addListener(stringify(_id), event::APP_INTERACT, onInteract);
}


AttributeInteractive::~AttributeInteractive()
{
    // empty
}

void AttributeInteractive::onInit() {
    Logger logger("AttributeInteractive");

    _posAttribute = getOrCreateSibling<AttributePosition>();
}

void AttributeInteractive::onInteract(event::Type type, event::EventData data) {
    Vector2 player = Vector2(data.getNumber("x"), data.getNumber("y"));
    Vector2 pos = Vector2(_posAttribute->getX(), _posAttribute->getY());

    // TODO: see if it's close!
    if( isCloseTo(player, pos)) {
        Logger logger("AttributeInteractive");
        logger.info("inteteracted!!!1!1!");

        auto imageAttr = getSibling<AttributeImage>();
        imageAttr->hide();
    }
}
