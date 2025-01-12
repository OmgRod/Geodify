#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <json.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

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

    auto contentBox = CCScale9Sprite::create("GJ_square01.png");
    contentBox->setContentSize({ winSize.width * 0.7f, winSize.height * 0.7f });
    contentBox->setPosition({ winSize.width / 2, (winSize.height / 2) - (winSize.height * 0.05f) });
    contentBox->setAnchorPoint({ 0.5f, 0.5f });
    contentBox->setID("content-box");
    this->addChild(contentBox);

    auto leftMenu = CCMenu::create();
    leftMenu->setAnchorPoint({ 0, 0 });
    leftMenu->setContentSize({ 0.f, winSize.height * 0.6f });
    leftMenu->setPosition({ winSize.width * 0.05f, winSize.height * 0.15f });
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
        menu_selector(GYSettingSelectLayer::generateWrapper)
    );
    colorBtn->setID("color-button");

    leftMenu->addChild(colorBtn);

    leftMenu->updateLayout();

    // auto testBtn = CCMenuItemSpriteExtra::create(
    //     CCSprite::createWithSpriteFrameName(
    //         "GJ_paintBtn_001.png"
    //     ),
    //     this,
    //     menu_selector(GYSettingSelectLayer::popup)
    // );

    // testBtn->setPosition(winSize.width * 0.5, winSize.height * 0.5);
    // menu->addChild(testBtn);

    this->addChild(leftMenu);
    this->addChild(menu);
    
    return true;
}

void GYSettingSelectLayer::generateWrapper(CCObject* sender) {
    generateModsList();
}
/*
bool GYSettingSelectLayer::generateModsList() {
    std::filesystem::path filePath = Mod::get()->getResourcesDir() / "layers.json";

    if (!std::filesystem::exists(filePath)) {
        log::error("File does not exist at path: {}", filePath.string());
        return false;
    }

    std::string filePathStr = filePath.string();
    log::info("Reading file from: {}", filePathStr);

    std::ifstream file(filePathStr);
    if (!file.is_open()) {
        log::error("Failed to open the file: {}", filePathStr);
        return false;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    log::info("File content: {}", fileContent);

    auto result = matjson::parse(fileContent);
    if (!result) {
        log::error("Failed to parse json: {}", result.unwrapErr());
        return false;
    }

    auto jsonData = result.unwrap();

    if (!jsonData.contains("mods") || !jsonData["mods"].isArray()) {
        log::error("Invalid JSON structure: 'mods' key not found or not an array");
        return false;
    }

    std::map<std::string, std::string> modsMap;
    for (const auto& mod : jsonData["mods"].array()) {
        std::string modName = mod.as<std::string>().unwrap();
        modsMap[modName] = modName;
    }

    log::info("Extracted Mods Map:");
    for (const auto& [modName, _] : modsMap) {
        log::info("- {}", modName);
    }

    return true;
}
*/