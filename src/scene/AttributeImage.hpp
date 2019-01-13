#ifndef _INCLUDE_ATTRIBUTETEXTURE_HPP
#define _INCLUDE_ATTRIBUTETEXTURE_HPP

#include "../Texture.hpp"
#include "../Device.hpp"
#include "../Renderable.hpp"

// #include "Attribute.hpp"
#include "AttributePosition.hpp"


enum Anchor {
	ANCHOR_TOP_LEFT,
	ANCHOR_TOP_CENTRE,
	ANCHOR_TOP_RIGHT,
	ANCHOR_MID_LEFT,
	ANCHOR_MID_CENTRE,
	ANCHOR_MID_RIGHT,
	ANCHOR_BOT_LEFT,
	ANCHOR_BOT_CENTRE,
	ANCHOR_BOT_RIGHT,
};

class AttributeImage: public Attribute {
public:
	static AttributeType type;
public:
    AttributeImage(Texture::smrtptr texture, Device::smrtptr device);
    virtual ~AttributeImage();

	// Lifecycle event response
	virtual void onInit();
	virtual void onUpdate(float delta);

	void setAnchor(Anchor anchor);

	// Change the renderer
	void hide();
	void show();

public:
    Texture::smrtptr _texture;
	Device::smrtptr _device;
	std::shared_ptr<AttributePosition> _posAttribute;
	Renderable _renderable;
	bool _isHidden;
	Anchor _anchor;
};

#endif /* end of include guard _INCLUDE_ATTRIBUTETEXTURE_HPP */
