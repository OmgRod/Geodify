#pragma once

#include <Geode/ui/General.hpp>

using namespace geode::prelude;

class SwelvyBG : public CCNode {
protected:
    bool init(float widthmult, float heightmul, float minspeed, float maxspeed);

    void updateSpritePosition(float dt);

public:
    static SwelvyBG* create(float widthmult = 1, float heightmul = 1, float minspeed = -1000, float maxspeed = 10000);
};
