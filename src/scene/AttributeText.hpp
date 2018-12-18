#ifndef _INCLUDE_ATTRIBUTETEXT_HPP
#define _INCLUDE_ATTRIBUTETEXT_HPP

#include "../String.hpp"
#include "../Font.hpp"
#include "../Device.hpp"
#include "Attribute.hpp"
#include "AttributeImage.hpp"

class AttributeText: public Attribute {
public:
	static AttributeType type;
public:
    AttributeText(const String& text, Font::smrtptr font, Device::smrtptr device);
    virtual ~AttributeText();

	virtual void onInit();

private:
    String _text;
	Font::smrtptr _font;
	Device::smrtptr _device;
	std::shared_ptr<AttributeImage> _imageAttribute;
};


#endif /* end of include guard: _INCLUDE_ATTRIBUTETEXT_HPP */
