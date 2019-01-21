#ifndef _INCLUDE_CAMERA_HPP
#define _INCLUDE_CAMERA_HPP

#include "core/Math.hpp"

class Camera {
public:
    Camera();
    ~Camera();

public:
    void moveTo(const Vector2 pos);
    const Vector2& getPos() const;
    void update(float delta);

private:
    Vector2 _position;
    Vector2 _desired;
    float _speed;
};

#endif /* end of include guard: _INCLUDE_CAMERA_HPP */
