#ifndef _INCLUDE_INPUT_HPP
#define _INCLUDE_INPUT_HPP

#include "Application.hpp"

enum KeyCode {
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_DOWN,
    KEY_COUNT= 255,
};

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

    float getAxis(const String& name);
    bool getButton(const String& name);

    // event listeners
    void onKeyDown(event::Type type, event::EventData data);
    void onKeyUp(event::Type type, event::EventData data);

private:
    Application& _app;
    String _id;
    std::map<String, KeyAxis> _keymap;
    bool _keys[255];
};



#endif /* end of include guard: _INCLUDE_INPUT_HPP */
