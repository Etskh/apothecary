#include "Events.hpp"

using namespace event;


// std::map<Type, CallbackList> _callbacks;

Dispatcher::Dispatcher() {
    // empty
}
Dispatcher::~Dispatcher() {
    // empty
}

void Dispatcher::send(Type eventType, const DataEntry& data) const {
    auto listener = _listeners.begin();
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
    while( listener != _listeners.end() ) {
        // TODO: Use crc32 for string comparison
        if( listener->name == name ) {
            _listeners.remove(*listener);
        }
        listener++;
    }
    return true;
}


/*
void Dispatcher::addListener(Type eventType, Callback callback) {
    _callbacks[eventType].push_back(callback);
}

bool Dispatcher::removeListener(Type eventType) {
    auto it = _callbacks.begin();
    while( it != _callbacks.end()) {
        auto callbackIterator = it->second.begin();
        while( callbackIterator != it->second.end() ) {
            if( *callbackIterator == callback ) {
                it->second.remove(callbackIterator);
            }
            callbackIterator++;
        }
        it++;
    }
    return false;
}
*/
