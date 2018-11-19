
#include <cstdio>

#include "Logger.hpp"



Logger::Logger(const char* name)
  : name(name) {
    // empty
}

void Logger::log(const char* str) const {
    info(str);
}
void Logger::info(const char* str) const {
    printf("INFO [%s] %s\n", name.c_str(), str);
}
void Logger::error(const char* str) const {
    printf("ERROR [%s] %s\n", name.c_str(), str);
}
