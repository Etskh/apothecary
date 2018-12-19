#ifndef _INCLUDE_EVENTLISTENER_HPP
#define _INCLUDE_EVENTLISTENER_HPP

#include <list>
#include <functional>

#include "String.hpp"
#include "DataEntry.hpp"

namespace event {

enum Type {
    Init,
    Update,
    Kill,
};

typedef std::function<void(Type, const DataEntry&)> Callback;

struct EventListener {
    String name;
    Callback callback;
    Type eventType;

    EventListener (const String& name, Type eventType, Callback callback)
        : name(name)
        , eventType(eventType)
        , callback(callback)
    {
        // empty
    }

    inline bool operator==(const EventListener& other) {
        return eventType == other.eventType;
    }
};

// #define CALLBACK(cls, func) std::bind()

class Dispatcher {
public:

    typedef std::list<Callback> CallbackList;

    Dispatcher();
    virtual ~Dispatcher();

    void send(Type eventType, const DataEntry& data) const;

    void addListener(const String& name, Type eventType, Callback callback);
    bool removeListener(const String& name, Type eventType);
    bool removeAllListeners(const String& name);

private:
    std::list<EventListener> _listeners;
};

} // namespace event

#endif /* end of include guard: _INCLUDE_EVENTLISTENER_HPP */
