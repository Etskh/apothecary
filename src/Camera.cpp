
#include "Camera.hpp"

Camera::Camera()
    : _position(0,0)
    , _desired(0,0)
    , _speed(0.003f) // pixels per second
{
    // empty
}

Camera::~Camera() {
    // empty
}

void Camera::moveTo(const Vector2 pos) {
    _desired = pos;
}

void Camera::update(float delta) {
    _position.lerp(_desired, delta * _speed);
}

const Vector2& Camera::getPos() const {
    return _position;
}
