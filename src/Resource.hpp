#ifndef _INCLUDE_RESOURCE_HPP
#define _INCLUDE_RESOURCE_HPP


class Resource {
public:
    Resource(const char* name);
    //Resource(Device* device);
    virtual ~Resource();
private:
    //Device* device;
    const char* resourceName;
};

#endif /* end of include guard: _INCLUDE_RESOURCE_HPP */
