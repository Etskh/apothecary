#ifndef _INCLUDE_ATTRIBUTETEXTURE_HPP
#define _INCLUDE_ATTRIBUTETEXTURE_HPP

#include "../Texture.hpp"
#include "../Device.hpp"
#include "../Renderable.hpp"

// #include "Attribute.hpp"
#include "AttributePosition.hpp"

class AttributeImage: public Attribute {
public:
	static AttributeType type;
public:
    AttributeImage(Texture::smrtptr texture, Device::smrtptr device);
    virtual ~AttributeImage();

	// Lifecycle event response
	virtual void onInit();
	virtual void onUpdate(float delta);

	// Change the renderer
	void hide();
	void show();

public:
    Texture::smrtptr _texture;
	Device::smrtptr _device;
	std::shared_ptr<AttributePosition> _posAttribute;
	Renderable _renderable;
	bool _isHidden;
};

#endif /* end of include guard _INCLUDE_ATTRIBUTETEXTURE_HPP */
