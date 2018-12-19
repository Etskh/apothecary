
#include "DataEntry.hpp"


DataEntry::DataEntry() {
    // empty
}

const char* DataEntry::getString(const char* name) const {
    return textList.at(name).c_str();
}
double DataEntry::getNumber(const char* name) const {
    return numberList.at(name);
}

void DataEntry::setString(const char* name, const char* val) {
    textList.insert( std::pair<std::string, std::string>(name, val));
}
void DataEntry::setNumber(const char* name, double val) {
    numberList.insert( std::pair<std::string, double>(name, val));
}
