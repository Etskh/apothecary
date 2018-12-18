#ifndef _INCLUDE_RENDERABLE_HPP
#define _INCLUDE_RENDERABLE_HPP

typedef unsigned int Renderable;

inline Renderable generateGuid() {
    static Renderable id = 0;
    return ++id;
}

#endif /* end of include guard: _INCLUDE_RENDERABLE_HPP */
