#ifndef _INCLUDE_INPUT_HPP
#define _INCLUDE_INPUT_HPP

#include "Application.hpp"

enum KeyCode {
    KEY_SPACE = 44,

    KEY_LEFT = 80,
    KEY_UP = 82,
    KEY_RIGHT = 79,
    KEY_DOWN = 81,

    KEY_COUNT= 255,
};

const char* etostr(KeyCode code);

struct KeyAxis {
    KeyCode neg;
    KeyCode pos;
};


class Input {
public:
    Input(Application& app);
    virtual ~Input();

    void setAxisMap(const String& name, KeyCode neg, KeyCode pos);
    void setButtonMap(const String& name, KeyCode code);

    float getAxis(const String& name) const;
    bool getButton(const String& name) const;

    // event listeners
    void onKeyDown(event::Type type, event::EventData data);
    void onKeyUp(event::Type type, event::EventData data);

    // Debug
    void print_r(String& output);

private:
    Application& _app;
    String _id;
    std::map<std::string, KeyCode> _buttonMap;
    std::map<std::string, KeyAxis> _keymap;
    bool _keys[KEY_COUNT];
};



#endif /* end of include guard: _INCLUDE_INPUT_HPP */
