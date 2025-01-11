#include <Geode/Geode.hpp>

#include "GYSettingSelectLayer.hpp"
#include "GYScreenshotPopup.hpp"

using namespace geode::prelude;

void GYSettingSelectLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

void GYSettingSelectLayer::backWrapper(CCObject* sender) {
    GYSettingSelectLayer::keyBackClicked();
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

void GYSettingSelectLayer::settingsBtn(CCObject* sender) {
    auto scene = CCScene::create();
    GYSettingSelectLayer* ret = new GYSettingSelectLayer();
    // Everything after this is not compiled
    if (ret && ret->init()) {
        ret->autorelease();
    }
    delete ret;
    ret = nullptr;
    scene->addChild(GYSettingSelectLayer::create());
    auto scenePrev = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(scenePrev);
}

bool GYSettingSelectLayer::init() {
    if (!CCLayer::init())
        return false;
    
    setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto menu = CCMenu::create();
    menu->setID("menu");

    auto background = CCSprite::create("GJ_gradientBG.png");
    background->setScaleX(CCDirector::sharedDirector()->getWinSize().width / background->getContentSize().width);
    background->setScaleY(CCDirector::sharedDirector()->getWinSize().height / background->getContentSize().height);
    background->setZOrder(-1);
    background->setColor({ 0, 102, 255 });
    background->setID("background");
    background->setPosition({ winSize.width / 2, winSize.height / 2 });
    this->addChild(background);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(GYSettingSelectLayer::backWrapper)
    );
    backBtn->setPosition(winSize.width * -0.45, winSize.height * 0.4);
    backBtn->setID("back-btn");
    menu->addChild(backBtn);

    auto title = CCLabelBMFont::create("Geodify Settings", "bigFont.fnt");
    title->setPosition(winSize.width / 2, winSize.height * 0.9);
    title->setID("title");
    this->addChild(title);

    auto leftMenu = CCMenu::create();
    leftMenu->setAnchorPoint({ 0, 0 });
    leftMenu->setContentSize({ 0.f, winSize.height * 0.6f });
    leftMenu->setPosition({ winSize.width * 0.1f, winSize.height * 0.2f });
    leftMenu->setID("left-menu");

    auto leftLayout = ColumnLayout::create();
    leftLayout->setAxis(Axis::Column);
    leftLayout->setGap(10.f);
    
    leftMenu->setLayout(leftLayout);

    auto colorBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName(
            "GJ_paintBtn_001.png"
        ),
        this,
        menu_selector(GYSettingSelectLayer::settingsBtn)
    );
    colorBtn->setID("color-button");

    leftMenu->addChild(colorBtn);

    leftMenu->updateLayout();

    this->addChild(leftMenu);
    this->addChild(menu);

    auto p = GYScreenshotPopup::create("MenuLayer");
    p->show();
    
    return true;
}