#ifndef _INCLUDE_SCENE_HPP
#define _INCLUDE_SCENE_HPP

#include <memory>
#include <vector>

#include "../Core.hpp"
#include "Attribute.hpp"


class SceneNode {
public:
    typedef std::shared_ptr<SceneNode> smrtptr;
public:
    SceneNode();
    SceneNode(const String& name);
    virtual ~SceneNode();

    // Lifecycle
    void update(float delta);

    // Children
    void addChild(SceneNode::smrtptr node);

    // Attributes
    void addAttribute(Attribute::smrtptr attribute);
    Attribute::smrtptr getAttribute(AttributeType type);
    template<class A, class... Args>
    void createAttribute(Args... args);
    template <class A>
    std::shared_ptr<A> get();

    void print_r(String& nodeText, size_t depth=0, bool isLastChild=true) const;

    static SceneNode::smrtptr Create(const String& name);
public:
    String name;
    Logger logger;

private:
    std::vector<SceneNode::smrtptr> _children;
    std::vector<Attribute::smrtptr> _attributes;
};


template<class A, class... Args>
void SceneNode::createAttribute(Args... args) {
    A* a = new A(args...);
    addAttribute(Attribute::smrtptr(a));
}

template <class A>
std::shared_ptr<A> SceneNode::get() {
    return std::dynamic_pointer_cast<A>(getAttribute(A::type));
}


#endif /* end of include guard: _INCLUDE_SCENE_HPP */
