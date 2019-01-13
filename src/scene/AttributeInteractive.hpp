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

	// Lifecycle
	virtual void onInit();
	virtual void onInteract(event::Type type, event::EventData data);

	// Access to members
	std::shared_ptr<AttributePosition> getPos();

	// For catching the event
	virtual void onActivate(event::EventData data) =0;

public:
	std::shared_ptr<AttributePosition> _posAttribute;
};

#endif /* end of include guard _INCLUDE_ATTRIBUTEINTERACTIVE_HPP */
