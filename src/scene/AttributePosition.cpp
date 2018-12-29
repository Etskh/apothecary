
#include "AttributePosition.hpp"

AttributeType AttributePosition::type = ATTRIBUTETYPE_POSITION;

AttributePosition::AttributePosition()
    : Attribute(AttributePosition::type)
{
    // empty
}

AttributePosition::~AttributePosition() {
	// empty
}

void AttributePosition::onInit() {
    // empty
}
