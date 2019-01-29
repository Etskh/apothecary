
#include "SceneNode.hpp"
#include "AttributePosition.hpp"

SceneNode::SceneNode(Application& app)
    : _app(app)
    , logger("SceneNode")
    , _id(createGuid())
{
    // empty
}

SceneNode::SceneNode(Application& app, const String& name)
    : _app(app)
    , name(name)
    , logger("SceneNode")
    , _id(createGuid())
{
    auto onUpdate = std::bind(&SceneNode::onUpdate, this, std::placeholders::_1, std::placeholders::_2);
    _app.addListener(stringify(_id), event::UPDATE, onUpdate);
}

SceneNode::~SceneNode() {
    _app.removeAllListeners(stringify(getId()));
}

void SceneNode::onUpdate(event::Type type, event::EventData data) {
    // TODO: get this from the eventData
    float delta = 0.016;
    for( auto it=_attributes.begin(); it != _attributes.end(); ++it) {
        (*it)->onUpdate(delta);
    }
}

void SceneNode::addChild(SceneNode::smrtptr node) {
    _children.push_back(node);
}

SceneNode::smrtptr SceneNode::find(const char* name) {
    SceneNode::smrtptr found = nullptr;
    for( auto it= _children.begin(); it != _children.end(); ++it) {
        // TODO: use CRC32
        if( (*it)->getName() == name ) {
            return *it;
        }
        found = (*it)->find(name);
    }
    if( !found ) {
        logger.warning("Cannot find child {}", name);
    }
    return found;
}

const String& SceneNode::getName() const {
    return name;
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
    String padding = "  ";
    //String padding = String().pad(depth);
    String sticks = isLastChild ? first : (depth == 0 ? first : middle);
    auto mainTemplateStr = String("\n{}{}{}");
    nodeText += format(mainTemplateStr, padding, sticks, name);
    for( auto attribute = _attributes.begin(); attribute != _attributes.end(); attribute++) {
        auto attrString = String("\n{}{}<attribute:{}>");
        nodeText += format(
            attrString,
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

SceneNode::smrtptr SceneNode::Create(Application& app, const String& name) {
    auto node = SceneNode::smrtptr(new SceneNode(app, name));
	node->addAttribute(Attribute::smrtptr(new AttributePosition()));
	return node;
}
