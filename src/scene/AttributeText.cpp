
#include "AttributeText.hpp"

AttributeType AttributeText::type = ATTRIBUTETYPE_TEXT;

AttributeText::AttributeText(const String& text, Font::smrtptr font, Device::smrtptr device)
    : Attribute(AttributeText::type)
    , _text(text)
    , _font(font)
    , _device(device)
    , _imageAttribute(nullptr)
{
    // empty
}

AttributeText::~AttributeText()
{
    // empty
}

void AttributeText::onInit() {
    auto texture = _font->createTexture(_text);
    _imageAttribute = getOrCreateSibling<AttributeImage>(texture, _device);
}
