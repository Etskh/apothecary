#ifndef _INCLUDED_LOGGER_HPP
#define _INCLUDED_LOGGER_HPP

#include <string>


class Logger {
public:
    Logger(const char* name);

    void log(const char* str) const;
    
    void info(const char* str) const;
    void error(const char* str) const;

private:
    std::string name;
};

#endif /* end of include guard: _INCLUDED_LOGGER_HPP */
