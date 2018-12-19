
#include "AttributePosition.hpp"

AttributeType AttributePosition::type = ATTRIBUTETYPE_POSITION;

AttributePosition::AttributePosition()
    : Attribute(AttributePosition::type)
    , isDirty(false)
{
    // empty
}

AttributePosition::~AttributePosition() {
	// empty
}

void AttributePosition::onInit() {
    // empty
}
