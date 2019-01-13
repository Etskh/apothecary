
#include "Attribute.hpp"

Attribute::Attribute(AttributeType type)
    : _type(type)
    , _parentGetter(nullptr)
    , _id(createGuid())
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
