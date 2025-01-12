#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include "../json.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

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

    nlohmann::json jsonData;
    try {
        jsonData = nlohmann::json::parse(fileContent);
    } catch (const nlohmann::json::parse_error& err) {
        log::error("Failed to parse JSON: {}", err.what());
        return false;
    }

    // Validate the structure of the "mods" key
    if (!jsonData.contains("mods") || !jsonData["mods"].is_object()) {
        log::error("Invalid JSON structure: 'mods' key not found or not an object");
        return false;
    }

    const auto& modsData = jsonData["mods"];
    std::map<std::string, std::pair<std::string, std::string>> modsMap;

    // Extract information about each mod
    for (auto it = modsData.begin(); it != modsData.end(); ++it) {
        const std::string modID = it.key();
        const auto& modInfo = it.value();

        // Validate mod structure
        if (!modInfo.contains("name") || !modInfo["name"].is_string() ||
            !modInfo.contains("author") || !modInfo["author"].is_string()) {
            log::error("Invalid mod entry: Missing 'name' or 'author' in mod '{}'", modID);
            continue;
        }

        std::string modName = modInfo["name"];
        std::string modAuthor = modInfo["author"];
        modsMap[modID] = { modName, modAuthor };
    }

    log::info("Extracted Mods Map:");
    for (const auto& [modID, modInfo] : modsMap) {
        log::info("- Mod ID: {}, Name: {}, Author: {}", modID, modInfo.first, modInfo.second);
    }

    // Process layers if needed
    if (jsonData.contains("layers") && jsonData["layers"].is_object()) {
        const auto& layersData = jsonData["layers"];
        log::info("Layers Info:");
        for (auto it = layersData.begin(); it != layersData.end(); ++it) {
            const std::string layerID = it.key();
            const auto& layerInfo = it.value();

            if (!layerInfo.contains("name") || !layerInfo["name"].is_string() ||
                !layerInfo.contains("mod") || !layerInfo["mod"].is_string()) {
                log::error("Invalid layer entry: Missing 'name' or 'mod' in layer '{}'", layerID);
                continue;
            }

            std::string layerName = layerInfo["name"];
            std::string modID = layerInfo["mod"];

            log::info("Layer ID: {}, Name: {}, Mod: {}", layerID, layerName, modID);

            // Optionally cross-reference with modsMap to provide more detailed info
            if (modsMap.find(modID) != modsMap.end()) {
                log::info("  - Linked Mod Name: {}, Author: {}", modsMap[modID].first, modsMap[modID].second);
            } else {
                log::warn("  - Mod ID '{}' not found in mods list", modID);
            }
        }
    } else {
        log::warn("No valid 'layers' data found in JSON");
    }

    return true;
}
