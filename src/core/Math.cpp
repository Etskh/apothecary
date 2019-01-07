
#include "Math.hpp"



bool isCloseTo(const Vector2& pos1, const Vector2& pos2) {
    static const float maxDistance = 64.f;
    float h = (pos1.x - pos2.x) * (pos1.x - pos2.x)
            + (pos1.y - pos2.y) * (pos1.y - pos2.y);

    return h < maxDistance;
}
