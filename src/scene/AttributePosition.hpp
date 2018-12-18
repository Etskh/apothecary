#ifndef _INCLUDE_ATTRIBUTEPOSITION_HPP
#define _INCLUDE_ATTRIBUTEPOSITION_HPP

#include "Attribute.hpp"

class AttributePosition: public Attribute {
public:
	static AttributeType type;

	/* enum Anchor {
		ANCHOR_TOP_LEFT,
		ANCHOR_TOP_CENTRE,
		ANCHOR_TOP_RIGHT,
		ANCHOR_MID_LEFT,
		ANCHOR_MID_CENTRE,
		ANCHOR_MID_RIGHT,
		ANCHOR_BOT_LEFT,
		ANCHOR_BOT_CENTRE,
		ANCHOR_BOT_RIGHT,
	}; */
public:
    AttributePosition();
    virtual ~AttributePosition();

	virtual void onInit();

	void set(float x, float y, float w, float h) {
		xPos = x;
		yPos = y;
		width = w;
		height = h;
	}

	inline int getX() const { return static_cast<int>(xPos); }
	inline int getY() const { return static_cast<int>(yPos); }
	inline int getWidth() const { return static_cast<int>(width); }
	inline int getHeight() const { return static_cast<int>(height); }

private:
	// Anchor anchor;
	float xPos;
	float yPos;
	float width;
	float height;
};


#endif /* end of include guard: _INCLUDE_ATTRIBUTEPOSITION_HPP */
