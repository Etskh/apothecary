
#include "Event.hpp"

Event::Event(const char* eventName)
    : type(crc32(eventName))
    , typeName(eventName)
{
    // empty
}

size_t Event::getType() const {
    return type;
}

bool Event::operator==(const char* eventName) const {
    return type == crc32(eventName);
}
