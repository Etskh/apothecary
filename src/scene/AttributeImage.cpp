
#include <cstdio>

#include "AttributeImage.hpp"

AttributeType AttributeImage::type = ATTRIBUTETYPE_IMAGE;

AttributeImage::AttributeImage(Texture::smrtptr texture, Device::smrtptr device)
    : Attribute(AttributeImage::type)
    , _texture(texture)
    , _device(device)
    , _renderable(0)
{
    // empty
}

AttributeImage::~AttributeImage()
{
    if( _renderable ) {
        _device->destroyRenderable(_renderable);
    }
}

void AttributeImage::onInit() {
    // get x and y
    // and w and h
    _posAttribute = getOrCreateSibling<AttributePosition>();
    _posAttribute->getX();
    _renderable = _device->createRenderableTexture(
        _texture,
        _posAttribute->getX(),
        _posAttribute->getY(),
        _posAttribute->getWidth(),
        _posAttribute->getHeight()
    );
}
