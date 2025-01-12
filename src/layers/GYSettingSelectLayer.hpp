#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYSettingSelectLayer : public CCLayer {
public:
    virtual void keyBackClicked();
    static CCScene* scene();
    static GYSettingSelectLayer* create();
    bool init();
    void settingsBtn(CCObject* sender);
    void backWrapper(CCObject* sender);
    void generateWrapper(CCObject* sender);
    void openNormalSettings(CCObject* sender);
    bool generateModsList();
};