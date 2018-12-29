#include "Events.hpp"

using namespace event;

Dispatcher::Dispatcher(const String& name)
    : logger(name)
{
    // empty
}
Dispatcher::~Dispatcher() {
    // empty
}

void Dispatcher::send(Type eventType, const EventData& data) const {
    auto listener = _listeners.begin();
    if( eventType != UPDATE) {
        logger.debug("Dispatching event {}", etostr(eventType));
    }

    while( listener != _listeners.end() ) {
        if( listener->eventType == eventType ) {
            listener->callback(eventType, data);
        }
        listener++;
    }
}

void Dispatcher::addListener(const String& name, Type eventType, Callback callback) {
    _listeners.push_back(EventListener(
        name,
        eventType,
        callback
    ));
    logger.info("Adding listener to [id:{}] for {}", name.c_str(), etostr(eventType));
}

bool Dispatcher::removeListener(const String& name, Type eventType) {
    auto listener = _listeners.begin();
    while( listener != _listeners.end() ) {
        // TODO: Use crc32 for string comparison
        if( listener->name == name ) {
            _listeners.remove(*listener);
            return true;
        }
        listener++;
    }
    return false;
}

bool Dispatcher::removeAllListeners(const String& name) {
    auto listener = _listeners.begin();
    logger.info("Removing listeners from [id:{}]", name.c_str());
    while( listener != _listeners.end() ) {
        // TODO: Use crc32 for string comparison
        if( listener->name == name ) {
            _listeners.remove(*listener);
        }
        listener++;
    }
    return true;
}
