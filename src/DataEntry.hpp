#ifndef _INCLUDED_DATAENTRY_HPP
#define _INCLUDED_DATAENTRY_HPP

#include <string>
#include <map>


class DataEntry {
public:
  DataEntry();

public:
    void setString(const char* name, const char* val);
    void setNumber(const char* name, double val);

    const char* getString(const char* name) const;
    double getNumber(const char* name) const;

private:
    std::map<std::string, std::string> textList;
    std::map<std::string, double> numberList;
};


#endif /* end of include guard: _INCLUDED_DATAENTRY_HPP */
