#ifndef _INCLUDED_LOGGER_HPP
#define _INCLUDED_LOGGER_HPP

#include <string>
#include <cstdio>

#include "String.hpp"

class Logger {
public:
    enum Colour {
        White,
        Blue,
        Red,
        Yellow,
        Green,
        Cyan,
        Magenta,
        Grey,
        Gray = Grey,
    };

public:
    Logger(const char* name);

    // TODO: fix terrible memory management - put this in the translation unit
    String& colourize(String& str, Colour colour) const {
        const String norm = "\033[0m";
        const String red = "\033[0;31m";
        const String green = "\033[0;32m";
        const String yellow = "\033[0;33m";
        const String blue = "\033[0;34m";
        const String magenta = "\033[0;35m";
        const String cyan = "\033[0;36m";
        const String gray = "\033[0;37m";
        switch(colour) {
        case White:
            str = gray + str + norm;
            break;
        case Red:
            str = red + str + norm;
            break;
        case Blue:
            str = blue + str + norm;
            break;
        case Yellow:
            str = yellow + str + norm;
            break;
        case Green:
            str = green + str + norm;
            break;
        case Cyan:
            str = cyan + str + norm;
            break;
        case Magenta:
            str = magenta + str + norm;
            break;
        case Grey: // also Gray
            str = gray + str + norm;
            break;
        default:
            // nothing
            break;
        }
        return str;
    }

    template<class ... Types>
    void log(const String& severity, const char* str, Types ... args) const {
        String appString("{} [{}] ");
        String nameString(name);
        format(appString, severity.c_str(), colourize(nameString, Grey).c_str());

        String userString(str);
        format(userString, args...);

        printf("%s%s\n", appString.c_str(), userString.c_str());
    }

    template<class ... Types>
    void debug(const char* str, Types ... args) const {
        String severity("DEBUG");
        // log(colourize(severity, Green), str, args...);
    }

    template<class ... Types>
    void info(const char* str, Types ... args) const {
        String severity("INFO");
        log(colourize(severity, Cyan), str, args...);
    }

    template<class ... Types>
    void warn(const char* str, Types ... args) const {
        String severity("WARN");
        log(colourize(severity, Yellow), str, args...);
    }

    template<class ... Types>
    void warning(const char* str, Types ... args) const {
        String severity("WARN");
        log(colourize(severity, Yellow), str, args...);
    }

    template<class ... Types>
    void error(const char* str, Types ... args) const {
        String severity("ERROR");
        log(colourize(severity, Red), str, args...);
    }

    inline const char* getName() const {
        return name.c_str();
    }

private:
    String name;
};

#endif /* end of include guard: _INCLUDED_LOGGER_HPP */
