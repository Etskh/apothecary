
#include "Input.hpp"


Input::Input(Application& app)
    : _app (app)
    , _id("input")
{
    // keydown
    auto onKeyDown = std::bind(&Input::onKeyDown, this, std::placeholders::_1, std::placeholders::_2);
    _app.addListener(_id, event::INPUT_KEYDOWN, onKeyDown);

    // keyup
    auto onKeyUp = std::bind(&Input::onKeyUp, this, std::placeholders::_1, std::placeholders::_2);
    _app.addListener(_id, event::INPUT_KEYUP, onKeyUp);
}

Input::~Input() {
    _app.removeAllListeners(_id);
}

void Input::setAxisMap(const String& name, KeyCode neg, KeyCode pos) {
    KeyAxis axis;
    axis.neg = neg;
    axis.pos = pos;
    _keymap.insert( std::pair<std::string, KeyAxis>(name.c_str(), axis));
}

void Input::setButtonMap(const String& name, KeyCode code) {
    // TODO: make me!
}

float Input::getAxis(const String& name) const {
    try {
        auto axis = _keymap.at(name.c_str());
        if (_keys[axis.neg] && !_keys[axis.pos]) {
            return -1.f;
        }
        else if (!_keys[axis.neg] && _keys[axis.pos]) {
            return 1.f;
        }
        return 0.f;
    }
    catch (std::out_of_range exception) {
        Logger logger("Input");
        logger.error("Unknown axis keymap \"{}\"", name);
        return 0.f;
    }
}

bool Input::getButton(const String& name) const {
    // TODO: make me!
    return false;
}

void Input::onKeyDown(event::Type type, event::EventData data) {
    Logger logger("Input");
    KeyCode code = static_cast<KeyCode>(data.getNumber("code"));
    logger.info("Recieved keydown {}", stringify(code));
    if( code > KEY_COUNT) {
        logger.error("Code larger than allocated key block {}", stringify(code));
        return;
    }
    _keys[code] = true;
}

void Input::onKeyUp(event::Type type, event::EventData data) {
    KeyCode code = static_cast<KeyCode>(data.getNumber("code"));
    if( code > KEY_COUNT) {
        Logger logger("Input");
        logger.error("Code larger than allocated key block {}", stringify(code));
        return;
    }
    _keys[code] = false;
}
