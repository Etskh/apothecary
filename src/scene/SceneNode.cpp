
#include "SceneNode.hpp"
#include "AttributePosition.hpp"

SceneNode::SceneNode()
    : logger("SceneNode")
{
    // empty
}

SceneNode::SceneNode(const String& name)
    : name(name)
    , logger("SceneNode")
{
    // empty
}

SceneNode::~SceneNode() {
    // empty
}

void SceneNode::addChild(SceneNode::smrtptr node) {
    _children.push_back(node);
}

Attribute::smrtptr SceneNode::getAttribute(AttributeType type) {
    for( auto it=_attributes.begin(); it != _attributes.end(); ++it) {
        if((*it)->getType() == type ) {
            return *it;
        }
    }
    // TODO: throw exception or handle error or something
    return Attribute::smrtptr(nullptr);
}

void SceneNode::addAttribute(Attribute::smrtptr attribute) {
    auto getter = std::bind(&SceneNode::getAttribute, this, std::placeholders::_1);
    auto adder = std::bind(&SceneNode::addAttribute, this, std::placeholders::_1);

    attribute->setParentGetter(getter);
    attribute->setParentAdder(adder);

    attribute->onInit();

    _attributes.push_back(attribute);
}

void SceneNode::print_r(String& nodeText, size_t depth, bool isLastChild) const {
    const char* first = "└─";
    const char* middle = "├─";
    const char* skip = "| ";
    const char* none = "  ";
    const size_t step = 2;
    String padding = String().pad(depth);
    String sticks = isLastChild ? first : (depth == 0 ? first : middle);
    nodeText += String("\n{}{}{}").format(padding, sticks, name);
    for( auto attribute = _attributes.begin(); attribute != _attributes.end(); attribute++) {
        nodeText += String("\n{}{}<attribute:{}>").format(
            padding,
            isLastChild ? none : skip,
            etostr((*attribute)->getType())
        );
    }
    for( auto child = _children.begin(); child != _children.end(); child++) {
        bool isLast = *child == _children.back();
        (*child)->print_r(nodeText, depth + step, isLast);
    }
}

SceneNode::smrtptr SceneNode::Create(const String& name) {
    auto node = SceneNode::smrtptr(new SceneNode(name));
	node->addAttribute(Attribute::smrtptr(new AttributePosition()));
	return node;
}
