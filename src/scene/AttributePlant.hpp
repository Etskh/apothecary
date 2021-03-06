#ifndef _INCLUDE_ATTRIBUTEPLANT_HPP
#define _INCLUDE_ATTRIBUTEPLANT_HPP

#include "AttributeInteractive.hpp"
#include "../Plants.hpp"

class AttributePlant: public AttributeInteractive {
public:
	static AttributeType type;
public:
    AttributePlant(Application* app, Ingredient ingredient);
    virtual ~AttributePlant();

	// For catching the event
	virtual void onActivate(event::EventData data);

	inline bool isActive() { return _isActive; }

private:
    Application* _app;
    Ingredient _ingredient;
	bool _isActive;
};


#endif /* end of include guard: _INCLUDE_ATTRIBUTEPLANT_HPP */
