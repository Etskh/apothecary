#ifndef _INCLUDE_ATTRIBUTEPLAYER_HPP
#define _INCLUDE_ATTRIBUTEPLAYER_HPP

#include "../Input.hpp"
#include "AttributePosition.hpp"

class AttributePlayer: public Attribute {
public:
	static AttributeType type;
public:
    AttributePlayer(const Input* input);
    virtual ~AttributePlayer();

	virtual void onInit();
	virtual void onUpdate(float delta);

public:
    const Input* _input;
	std::shared_ptr<AttributePosition> _attrPos;

	float _height; // in metres
	float _speed; // in metres per second
	float _ratio; // pixels to metre
};


#endif /* end of include guard: _INCLUDE_ATTRIBUTEPLAYER_HPP */
