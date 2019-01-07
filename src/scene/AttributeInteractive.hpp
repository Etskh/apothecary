#ifndef _INCLUDE_ATTRIBUTEINTERACTIVE_HPP
#define _INCLUDE_ATTRIBUTEINTERACTIVE_HPP

// #include "Attribute.hpp"
#include "AttributePosition.hpp"
#include "../Core.hpp"
#include "../Application.hpp"

class AttributeInteractive: public Attribute {
public:
	static AttributeType type;
public:
    AttributeInteractive(Application* app);
    virtual ~AttributeInteractive();

	virtual void onInit();
	virtual void onInteract(event::Type type, event::EventData data);

public:
    Guid _id;
	std::shared_ptr<AttributePosition> _posAttribute;
};

#endif /* end of include guard _INCLUDE_ATTRIBUTEINTERACTIVE_HPP */
