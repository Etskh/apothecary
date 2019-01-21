
#include "Attribute.hpp"

Attribute::Attribute(AttributeType type)
    : _id(createGuid())
    , _type(type)
    , _parentGetter(nullptr)
{
    // empty
}


Attribute::~Attribute() {
    // empty
}

void Attribute::setParentGetter(ParentGetter getter) {
    _parentGetter = getter;
}

void Attribute::setParentAdder(ParentAdder adder) {
    _parentAdder = adder;
}
