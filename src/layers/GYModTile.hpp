#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYModTile : public CCLayer {
public:
    void viewMod(CCObject* sender);
    static GYModTile* create(const char *modName, const char *modAuthor, const char *modID);
    bool init(const char *modName, const char *modAuthor, const char *modID);

    std::string m_modID;
    std::string m_modName;
    std::string m_modAuthor;
};