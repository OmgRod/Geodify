#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYSettingSelectLayer : public CCLayer {
public:
    virtual void KeyBackClicked();
    static CCScene* scene();
    static GYSettingSelectLayer* create();
    bool init();
    void settingsBtn(CCObject*);
};