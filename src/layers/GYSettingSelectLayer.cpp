#include <Geode/Geode.hpp>

#include "GYSettingSelectLayer.hpp"

using namespace geode::prelude;

void GYSettingSelectLayer::KeyBackClicked() {
    CCDirector::get()->popScene();
}

CCScene* GYSettingSelectLayer::scene() {
    auto scene = CCScene::create();
    scene->addChild(GYSettingSelectLayer::create());
    return scene;
}

GYSettingSelectLayer* GYSettingSelectLayer::create() {
    GYSettingSelectLayer* ret = new GYSettingSelectLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

void GYSettingSelectLayer::settingsBtn(CCObject*) {
    auto scenePrev = CCTransitionFade::create(0.5f, GYSettingSelectLayer::scene());
    CCDirector::sharedDirector()->pushScene(scenePrev);
}

bool GYSettingSelectLayer::init() {
    if (!GYSettingSelectLayer::init())
        return false;
    
    setKeyboardEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();

    auto background = CCSprite::create("GJ_gradientBG.png");
    background->setScaleX(CCDirector::sharedDirector()->getWinSize().width / background->getContentSize().width);
    background->setScaleY(CCDirector::sharedDirector()->getWinSize().height / background->getContentSize().height);
    background->setZOrder(-1);
    background->setColor({ 0, 102, 255 });
    background->setID("background");
    background->setPosition({ 0.f, 0.f });
    this->addChild(background);
    
    return true;
}