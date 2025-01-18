#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYModTile : public CCLayer {
public:
    void viewMod(CCObject* sender);
    static GYModTile* create(std::string modName, std::string modAuthor, std::string modID);
    bool init(std::string modName, std::string modAuthor, std::string modID);

    std::string m_modID;
    std::string m_modName;
    std::string m_modAuthor;
};