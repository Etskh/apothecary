#ifndef _INCLUDE_ATTRIBUTE_HPP
#define _INCLUDE_ATTRIBUTE_HPP


#include <memory>
#include <functional>


enum AttributeType {
    ATTRIBUTETYPE_NONE,
    ATTRIBUTETYPE_TEXT,
    ATTRIBUTETYPE_IMAGE,
    ATTRIBUTETYPE_POSITION,
};

inline const char* etostr(AttributeType t) {
	static const char* str[] = {
		"none",
		"text",
		"image",
		"position",
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

    virtual void onInit() = 0;

private:
    AttributeType _type;
    ParentGetter _parentGetter;
    ParentAdder _parentAdder;
};


template<class A, class... Args>
std::shared_ptr<A> Attribute::getOrCreateSibling(Args ...args) {
    printf("Looking for attribute:%s\n", etostr(A::type));
    Attribute::smrtptr attribute = _parentGetter(A::type);
    if( !attribute ) {
        printf("Cannot find, creating new one\n");
        attribute = Attribute::smrtptr(new A(args...));
        _parentAdder(attribute);
    }
    printf("Found- casting back\n");
    return std::dynamic_pointer_cast<A>(attribute);
}


#endif /* end of include guard: _INCLUDE_ATTRIBUTE_HPP */
