#ifndef _INCLUDE_EVENTLISTENER_HPP
#define _INCLUDE_EVENTLISTENER_HPP

#include <list>
#include <functional>

#include "String.hpp"
#include "DataEntry.hpp"
#include "Logger.hpp"

namespace event {

enum Type {
    Init,
    Update,
    Kill,
    Input_MouseUp,
    Input_MouseDown,
    Input_MouseMove,
};

typedef DataEntry EventData;

typedef std::function<void(Type, const EventData&)> Callback;

struct EventListener {
    String name;
    Type eventType;
    Callback callback;

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

    Dispatcher(const String& name);
    virtual ~Dispatcher();

    void send(Type eventType, const DataEntry& data) const;

    void addListener(const String& name, Type eventType, Callback callback);
    bool removeListener(const String& name, Type eventType);
    bool removeAllListeners(const String& name);

public:
    Logger logger;

private:
    std::list<EventListener> _listeners;
};

} // namespace event

#endif /* end of include guard: _INCLUDE_EVENTLISTENER_HPP */
