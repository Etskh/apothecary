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

    void smoothInOut(const Vector2& destination, float t);

    bool isCloseTo(const Vector2& other);

    static void smooth(Vector2& out, const Vector2& start, const Vector2& end, float t);
};


/*

out RangeMap( in, inStart, inEnd, outStart, outEnd) {
    out = in - inStart; // Puts in [0, inEnd - inStart]
    out /= inEnd - inStart;
    out = EASING_FUNCTION(out);
    out *= outEnd - outStart;
    return out + outStart;
}

*/



bool isCloseTo(const Vector2& pos1, const Vector2& pos2);


#endif /* end of include guard: _INCLUDE_MATH_HPP */
