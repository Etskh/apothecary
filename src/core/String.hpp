#ifndef _INCLUDE_STRING_HPP
#define _INCLUDE_STRING_HPP

#include <string>
#include <vector>
#include <cstring>

class String {
public:
    String();
    String(size_t num);
    String(const char* str);
    String(std::string str);

    template<class ...Types>
    String& format(Types ... args);

    String& pad(size_t count, char character=' ');

    const char* c_str() const;

    operator const char*() const;
    String operator +(const char* str) const;
    String& operator +=(const char* str);

private:
    std::string value;
};



template<class ...Types>
String& String::format(Types ... args) {
    const char* replacement = "{}";
    std::vector<String> vec = {args...};
    for (size_t i = 0; i < vec.size(); ++i) {
        auto occurence = value.find(replacement);
        if( occurence == std::string::npos ) {
            // TODO: affix the value to the end as separate commas
        }
        else {
            value.replace(occurence, strlen(replacement), vec[i]);
        }
    }
    return *this;
}


#endif /* end of include guard: _INCLUDE_STRING_HPP */
