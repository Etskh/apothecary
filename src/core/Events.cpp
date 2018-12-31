#include "Events.hpp"

#include <algorithm>

using namespace event;

Dispatcher::Dispatcher(const String& name)
    : logger(name.c_str())
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
    auto finder = [name] (const EventListener& listener) {
        return listener.name == name;
    };
    auto found = std::find_if(_listeners.begin(), _listeners.end(), finder);
    if( found == _listeners.end() ) {
        logger.error("Could not remove listeners");
        return false;
    }
    logger.info("Removed listener");
    _listeners.remove(*found);
    return true;
}

size_t Dispatcher::removeAllListeners(const String& name) {
    size_t sum = 0;
    auto finder = [name] (const EventListener& listener) {
        return listener.name == name;
    };
    // Keep looking until we don't find anything
    std::list<EventListener>::iterator found;
    while((found = std::find_if(_listeners.begin(), _listeners.end(), finder))
        != _listeners.end()) {
        _listeners.remove(*found);
        sum += 1;
    }
    logger.info("Removed {} listeners", stringify(sum));
    return sum;
}
