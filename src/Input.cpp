
#include "Input.hpp"

const char* etostr(KeyCode code) {
    switch(code) {
    case KEY_UP: return "KEY_UP";
    case KEY_LEFT: return "KEY_LEFT";
    case KEY_RIGHT: return "KEY_RIGHT";
    case KEY_DOWN: return "KEY_DOWN";
    case KEY_SPACE: return "KEY_SPACE";
    case KEY_B: return "KEY_B";
    default:
        Logger logger("Input");
        logger.error("Unknown string for code {}", stringify(code));
        return "Unknown";
    }
}


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
    _buttonMap.insert( std::pair<std::string, KeyCode>(name.c_str(), code));
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
    try {
        KeyCode code = _buttonMap.at(name.c_str());
        return _keys[code];
    }
    catch (std::out_of_range exception) {
        Logger logger("Input");
        logger.error("Unknown button keymap \"{}\"", name);
        return true;
    }
    return false;
}

void Input::onKeyDown(event::Type type, event::EventData data) {
    Logger logger("Input");
    KeyCode code = static_cast<KeyCode>(data.getNumber("code"));
    logger.debug("Recieved keydown {}", stringify(code));
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

void Input::print_r(String& output) {
    auto axis = _keymap.begin();
    while( axis != _keymap.end()) {
        output += String("\n");
        output += String(" [") + axis->first + "]: ";
        output += String(etostr(axis->second.neg));
        output += " and ";
        output += String(etostr(axis->second.pos));
        axis++;
    }

    auto button = _buttonMap.begin();
    while( button != _buttonMap.end()) {
        output += String("\n");
        output += String(" [") + button->first + "]: ";
        output += String(etostr(button->second));
        button++;
    }
}
