
#include "Math.hpp"

#include <cmath>
#include <cstdio>


/*
https://en.wikipedia.org/wiki/Linear_interpolation

// Imprecise method, which does not guarantee v = v1 when t = 1, due to floating-point arithmetic error.
// This form may be used when the hardware has a native fused multiply-add instruction.
float lerp(float v0, float v1, float t) {
  return v0 + t * (v1 - v0);
}

float lerp(float v0, float v1, float t) {
  return (1 - t) * v0 + t * v1;
}

*/
void Vector2::lerp(const Vector2& destination, float delta) {
    x = (1 - delta) * x + delta * destination.x;
    y = (1 - delta) * y + delta * destination.y;
}

bool Vector2::isCloseTo(const Vector2& other) {
    return ::isCloseTo(*this, other);
}


bool isCloseTo(const Vector2& pos1, const Vector2& pos2) {
    static const float maxDistance = pow(32.f, 2);

    float hypotenuseSquared =
        pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2);

    return hypotenuseSquared < maxDistance;
}
