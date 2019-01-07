#ifndef _INCLUDE_ATTRIBUTE_HPP
#define _INCLUDE_ATTRIBUTE_HPP


#include <memory>
#include <functional>


#include "../core/Logger.hpp"


enum AttributeType {
    ATTRIBUTETYPE_NONE,
    ATTRIBUTETYPE_TEXT,
    ATTRIBUTETYPE_IMAGE,
    ATTRIBUTETYPE_POSITION,
    ATTRIBUTETYPE_INTERACTIVE,
};

inline const char* etostr(AttributeType t) {
	static const char* str[] = {
		"none",
		"text",
		"image",
		"position",
        "interactive",
	};
	return str[t];
}


class Attribute {
public:
    typedef std::shared_ptr<Attribute> smrtptr;
    typedef std::function<Attribute::smrtptr(AttributeType)> ParentGetter;
    typedef std::function<void(Attribute::smrtptr)> ParentAdder;

public:
    Attribute(AttributeType type);
    virtual ~Attribute();

public:
    inline AttributeType getType() const { return _type; }
    void setParentGetter(ParentGetter getter);
    void setParentAdder(ParentAdder adder);

    template<class A, class... Args>
    std::shared_ptr<A> getOrCreateSibling(Args ...args);
    template<class A>
    std::shared_ptr<A> getSibling();

    // Lifecycle
    virtual void onInit() = 0;
    virtual void onUpdate(float delta) {}
    virtual void onKill() {}

    // Serialization
    // virtual bool save(String& output);
    // virtual bool load(const String& input);

private:
    AttributeType _type;
    ParentGetter _parentGetter;
    ParentAdder _parentAdder;
};


template<class A, class... Args>
std::shared_ptr<A> Attribute::getOrCreateSibling(Args ...args) {
    Logger logger("Attribute");
    Attribute::smrtptr attribute = _parentGetter(A::type);

    logger.debug("Looking for attribute: {}", etostr(A::type));

    if( !attribute ) {
        logger.debug("Cannot find one, creating new one");

        attribute = Attribute::smrtptr(new A(args...));
        _parentAdder(attribute);
    }
    return std::dynamic_pointer_cast<A>(attribute);
}

template<class A>
std::shared_ptr<A> Attribute::getSibling() {
    Logger logger("Attribute");
    Attribute::smrtptr attribute = _parentGetter(A::type);
    logger.debug("Looking for attribute: {}", etostr(A::type));

    if( !attribute ) {
        logger.error("Cannot find one");
    }
    return std::dynamic_pointer_cast<A>(attribute);
}


#endif /* end of include guard: _INCLUDE_ATTRIBUTE_HPP */
