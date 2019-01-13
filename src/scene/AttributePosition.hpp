#ifndef _INCLUDE_ATTRIBUTEPOSITION_HPP
#define _INCLUDE_ATTRIBUTEPOSITION_HPP

#include "Attribute.hpp"
#include "../core/Math.hpp"
#include "../core/Logger.hpp"

class AttributePosition: public Attribute {
public:
	static AttributeType type;
public:
    AttributePosition();
    virtual ~AttributePosition();

	virtual void onInit();

	void set(float x, float y, float w, float h) {
		posX = x;
		posY = y;
		width = w;
		height = h;
	}

	inline int getX() const { return static_cast<int>(posX); }
	inline int getY() const { return static_cast<int>(posY); }
	inline int getWidth() const { return static_cast<int>(width); }
	inline int getHeight() const { return static_cast<int>(height); }

	inline bool getRect(Rect2d* out) const {
		if( out == nullptr ) {
			return false;
		}
		out->posX = posX;
		out->posY = posY;
		out->width = width;
		out->height = height;
		return true;
	}

	inline void moveBy (float x, float y) {
		posX += x;
		posY += y;
	}

private:
	// Anchor anchor;
	float posX;
	float posY;
	float width;
	float height;
};


#endif /* end of include guard: _INCLUDE_ATTRIBUTEPOSITION_HPP */
