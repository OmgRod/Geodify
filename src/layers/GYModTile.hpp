#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYModTile : public CCLayer {
public:
    static GYModTile* create();
    bool init();
};