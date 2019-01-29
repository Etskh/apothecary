
#include <cstdio>

#include "AttributePlayer.hpp"

AttributeType AttributePlayer::type = ATTRIBUTETYPE_PLAYER;

AttributePlayer::AttributePlayer(const Input* input)
    : Attribute(AttributePlayer::type)
    , _input(input)
    , _height(2.f)
    , _speed(4.f)
    , _ratio(1.f)
    , _allowMovement(true)
{
    // empty
}


AttributePlayer::~AttributePlayer()
{
    // empty
}

void AttributePlayer::allowMovement(bool allow) {
    _allowMovement = allow;
}

void AttributePlayer::onInit() {
    _attrPos = getOrCreateSibling<AttributePosition>();

    _ratio = _attrPos->getHeight() / _height;
}

void AttributePlayer::onUpdate(float delta) {
    if( _allowMovement ) {

        float deltaMov = _speed * _ratio * delta;
        // Gathering deltas based on input
        float deltaX = deltaMov * _input->getAxis("walk.x");
        float deltaY = deltaMov * _input->getAxis("walk.y");
        _attrPos->moveBy(deltaX, deltaY);
    }
}
