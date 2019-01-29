
#include "Math.hpp"

#include <cmath>
#include <cstdio>

//
// Map a range [a,b] -> [0,1] then ease it based on in, then back to [a,b]
//
inline float rangeMap(float t, float(*ease)(float), float start, float end) {
    float out = (*ease)((t - start) / (end - start));
    return (out * (end - start)) + start;
}

//
// Blend two easing functions
//
inline float blendEase(float t, float(*ease1)(float), float(*ease2)(float)) {
    float a = (*ease1)(t);
    float b = (*ease2)(t);
    return a + t * (b - a);
}

//
// Easing functions
//
inline float smoothStart(float t) {
    return t * t * t;
}
inline float smoothStop(float t) {
    return 1 - (smoothStart(1-t));
}
inline float easeInOut(float t) {
    return blendEase(t, smoothStart, smoothStop);
}

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

void Vector2::smooth(Vector2& out, const Vector2& start, const Vector2& end, float t) {
    out.x = rangeMap(t, easeInOut, start.x, end.x);
    out.y = rangeMap(t, easeInOut, start.y, end.y);
}





bool isCloseTo(const Vector2& pos1, const Vector2& pos2) {
    static const float maxDistance = pow(32.f, 2);

    float hypotenuseSquared =
        pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2);

    return hypotenuseSquared < maxDistance;
}
