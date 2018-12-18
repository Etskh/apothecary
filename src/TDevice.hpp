#ifndef _INCLUDE_TDEVICE_HPP
#define _INCLUDE_TDEVICE_HPP

#include <cstdio>

#include <map>

#include "Device.hpp"
#include "Renderable.hpp"

template <class TRenderable>
class TDevice: public Device {
public:
    inline TDevice()
        : Device() {
        // empty
    }
    virtual ~TDevice() {
        // empty
    }

public:
    typedef std::pair<Renderable, TRenderable> Element;
    typedef std::map<Renderable, TRenderable> RenderableMap;

public:
    Renderable createRenderable(const TRenderable& renderableConfig);
    bool destroyRenderable(Renderable renderable);

protected:
    RenderableMap _renderables;
};


template <class TRenderable>
Renderable TDevice<TRenderable>::createRenderable(const TRenderable& config) {
    Renderable id = generateGuid();
    _renderables.insert(Element(id, config));
    return id;
}


template <class TRenderable>
bool TDevice<TRenderable>::destroyRenderable(Renderable renderable) {
    auto it = _renderables.find(renderable);
    if( it == _renderables.end() ) {
        return false;
    }
    // printf("Before erase\n");
    _renderables.erase (it);
    return true;
}


#endif /* end of include guard: _INCLUDE_TDEVICE_HPP */
