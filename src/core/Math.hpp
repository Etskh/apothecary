#ifndef _INCLUDE_MATH_HPP
#define _INCLUDE_MATH_HPP

struct Rect2d {
    float posX;
    float posY;
    float width;
    float height;
};

struct Vector2 {
    float x;
    float y;

    Vector2(float _x, float _y)
        : x(_x)
        , y(_y)
    {
        // empty
    }

    void lerp(const Vector2& destination, float delta);

    bool isCloseTo(const Vector2& other);
};


bool isCloseTo(const Vector2& pos1, const Vector2& pos2);


#endif /* end of include guard: _INCLUDE_MATH_HPP */
