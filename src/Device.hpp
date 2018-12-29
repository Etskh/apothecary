#ifndef _INCLUDE_DEVICE_HPP
#define _INCLUDE_DEVICE_HPP

#include <memory>
#include <vector>

#include "core/DataEntry.hpp"
#include "core/Math.hpp"
#include "Renderable.hpp"
#include "Font.hpp"
#include "Texture.hpp"

// #include "scene/SceneNode.hpp"


class Device {
public:
    typedef std::shared_ptr<Device> smrtptr;
    virtual ~Device();
public:
    virtual bool init(const DataEntry& config) = 0;
    virtual int run(void) = 0;
    virtual void render(float delta) = 0;

    virtual Font::smrtptr createFont (const char* fontName) = 0;
    virtual Texture::smrtptr createTexture(const char* path) = 0;

    virtual Renderable createRenderableTexture (Texture::smrtptr tex, const Rect2d& rect) = 0;
    virtual bool updateRenderableTexture (Renderable texture, const Rect2d& rect) = 0;
    virtual bool destroyRenderable (Renderable renderable) = 0;


protected:
    Device();
};


#endif /* end of include guard: _INCLUDE_DEVICE_HPP */
