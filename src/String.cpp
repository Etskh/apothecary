
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

String::operator const char*() const {
    return value.c_str();
}

const char* String::c_str() const {
    return value.c_str();
}
