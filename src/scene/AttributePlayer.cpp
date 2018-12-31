
#include <cstdio>

#include "AttributePlayer.hpp"

AttributeType AttributePlayer::type = ATTRIBUTETYPE_IMAGE;

AttributePlayer::AttributePlayer(const Input* input)
    : Attribute(AttributePlayer::type)
    , _input(input)
    , _height(2.f)
    , _speed(4.f)
    , _ratio(1.f)
{
    // empty
}


AttributePlayer::~AttributePlayer()
{
    // empty
}

void AttributePlayer::onInit() {
    _attrPos = getOrCreateSibling<AttributePosition>();

    _ratio = _attrPos->getHeight() / _height;
}

void AttributePlayer::onUpdate(float delta) {
    float deltaMov = _speed * _ratio * delta;

    // Gathering deltas based on input
    float deltaX = deltaMov * _input->getAxis("walk.x");
    float deltaY = deltaMov * _input->getAxis("walk.y");
    _attrPos->moveBy(deltaX, deltaY);
}
