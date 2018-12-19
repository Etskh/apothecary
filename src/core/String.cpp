
#include <string>
#include <cstdio>

#include "String.hpp"

String::String() {
    // empty
}

String::String(size_t num)
    : value(std::to_string(num))
{
    // empty
}

String::String(const char* str)
    : value(str)
{
    // empty
}

String::String(std::string str)
    : value(str)
{
    // empty
}

String& String::pad(size_t count, char character) {
    for(size_t c=0; c<count; ++c) {
        value += character;
    }
    return *this;
}


String::operator const char*() const {
    return c_str();
}

String String::operator +(const char* str) const {
    return String(value + str);
}

String& String::operator +=(const char* str) {
    value += str;
    return *this;
}


const char* String::c_str() const {
    return value.c_str();
}
