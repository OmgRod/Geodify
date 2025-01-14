#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYModTile : public CCLayer {
public:
    void viewMod(CCObject* sender);
    static GYModTile* create(const char *modName, const char *modAuthor, const char *modID, int tag);
    bool init(const char *modName, const char *modAuthor, const char *modID, int tag);
};