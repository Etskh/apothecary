
#include <cstdio>

#include "AttributeImage.hpp"

AttributeType AttributeImage::type = ATTRIBUTETYPE_IMAGE;

AttributeImage::AttributeImage(Texture::smrtptr texture, Device::smrtptr device)
    : Attribute(AttributeImage::type)
    , _texture(texture)
    , _device(device)
    , _renderable(0)
    , _isHidden(false)
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
    Rect2d rect;
    Logger logger("AttributeImage");

    _posAttribute = getOrCreateSibling<AttributePosition>();
    if( !_posAttribute->getRect(&rect)) {
        logger.warning("Could not get the rect for the _posAttribute");
        return;
    }

    _renderable = _device->createRenderableTexture(_texture, rect);
    if( !_renderable ) {
        logger.warning("Couldn't get the renderable");
        return;
    }
}

void AttributeImage::onUpdate(float delta) {
    Rect2d rect;
    Logger logger("AttributeImage");
    if( !_posAttribute->getRect(&rect)) {
        logger.warning("Couldnt not get the rect from the _posAttribute");
        return;
    }

    _device->updateRenderableTexture(_renderable, rect, _isHidden);
}

void AttributeImage::show() {
    _isHidden = false;
}

void AttributeImage::hide() {
    _isHidden = true;
}
