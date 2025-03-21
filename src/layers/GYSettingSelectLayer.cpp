#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/cocos.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>

#include "GYSettingSelectLayer.hpp"
#include "GYColorPopup.hpp"
#include "GYModTile.hpp"
#include "../SwelvyBG.hpp"
#include "../json.hpp"

/*

BREAKING NEWS:

OmgRod hates scrolling stuff.

*/


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

void GYSettingSelectLayer::colorPopup(CCObject* sender) {
    GYColorPopup::create()->show();
}

void GYSettingSelectLayer::openNormalSettings(CCObject* sender) {
    Mod::get()->setSavedValue("settingsBtnClicked", true);
    openSettingsPopup(Mod::get());
}

bool GYSettingSelectLayer::init() {
    if (!CCLayer::init())
        return false;
    
    setKeypadEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    CCMenu* menu = CCMenu::create();
    menu->setID("menu");

    if (Mod::get()->getSettingValue<bool>("omgrod.geodify/GYSettingSelectLayer")) {
        auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-1);
		this->addChild(swelvyBG);
    } else {
        CCSprite* background = CCSprite::create("GJ_gradientBG.png");
        background->setScaleX(CCDirector::sharedDirector()->getWinSize().width / background->getContentSize().width);
        background->setScaleY(CCDirector::sharedDirector()->getWinSize().height / background->getContentSize().height);
        background->setZOrder(-1);
        background->setColor({ 0, 102, 255 });
        background->setID("background");
        background->setPosition({ winSize.width / 2, winSize.height / 2 });
        this->addChild(background);
    }

    CCSprite* cornerLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    cornerLeft->setPosition(CCPoint(winSize.width * 0, winSize.height * 0));
    cornerLeft->setAnchorPoint(CCPoint(0, 0));
    cornerLeft->setID("corner-left");
    this->addChild(cornerLeft);

    CCSprite* cornerRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    cornerRight->setPosition(CCPoint(winSize.width * 1, winSize.height * 0));
    cornerRight->setAnchorPoint(CCPoint(1, 0));
    cornerRight->setFlipX(true);
    cornerRight->setID("corner-right");
    this->addChild(cornerRight);

    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(GYSettingSelectLayer::backWrapper)
    );
    backBtn->setPosition(winSize.width * -0.45, winSize.height * 0.4);
    backBtn->setID("back-btn");
    menu->addChild(backBtn);

    CCLabelBMFont* title = CCLabelBMFont::create("Geodify Settings", "bigFont.fnt");
    title->setPosition(winSize.width / 2, winSize.height * 0.9);
    title->setID("title");
    this->addChild(title);


    // START OF CONTENT

    CCScale9Sprite* contentBox = CCScale9Sprite::create("square02b_001.png");
    contentBox->setColor(ccColor3B{0, 0, 0});
    contentBox->setOpacity(60);
    contentBox->setContentSize({ winSize.width * 0.7f, winSize.height * 0.7f });
    contentBox->setPosition({ winSize.width / 2, winSize.height / 2 - winSize.height * 0.05f });
    contentBox->setAnchorPoint({ 0.5f, 0.5f });
    contentBox->setID("content-box");
    this->addChild(contentBox);

    ScrollLayer* scroll = ScrollLayer::create({ winSize.width * 0.7f, winSize.height * 0.7f }, true, true);
    scroll->setID("scroll");
    scroll->setTouchEnabled(true);
    contentBox->addChild(scroll);

    auto contentLayer = CCLayer::create();
    contentLayer->setContentSize({ winSize.width * 0.7f, 0.f });
    contentLayer->setID("content-layer");
    contentLayer->setPosition({ 0, 0 });
    contentLayer->setAnchorPoint({ 0, 0 });

    auto columnLayout = ColumnLayout::create();
    columnLayout->setAxisReverse(true)
                ->setAutoGrowAxis(scroll->getContentHeight())
                ->setCrossAxisOverflow(false)
                ->setAxisAlignment(AxisAlignment::Center)
                ->setGap(10.f);
    contentLayer->setLayout(columnLayout);

    auto modTiles = { 
        GYModTile::create("Geometry Dash", "RobTop", "gd"),
        GYModTile::create("Geode", "Geode Team", "geode.loader"),
        GYModTile::create("BetterInfo", "Cvolton", "cvolton.betterinfo"),
        GYModTile::create("Globed", "dankmeme", "dankmeme.globed2"),
        GYModTile::create("Texture Loader", "Geode Team", "geode.texture-loader"),
        GYModTile::create("Integrated Demonlist", "hiimjustin000", "hiimjustin000.integrated_demonlist"),
        GYModTile::create("GDPS Switcher", "km7dev", "km7dev.gdps-switcher"),
        GYModTile::create("BetterAchievements", "limegradient", "limegradient.betterachievements"),
        GYModTile::create("GDDP Integration", "Minemaker0430", "minemaker0430.gddp_integration"),
        GYModTile::create("Garage Plus", "OmgRod", "omgrod.garage_plus"),
        // GYModTile::create("GDStream", "OmgRod", "omgrod.gdstream"),
        GYModTile::create("Geodify", "OmgRod & Cosmella-v", "omgrod.geodify"),
        // GYModTile::create("Newgrounds Explorer", "TheSillyDoggo", "thesillydoggo.newgrounds_explorer"),
        GYModTile::create("Texture Workshop", "Uproxide", "uproxide.textures"),
        GYModTile::create("Geometry Dash: Odyssey", "chumiu", "teamtcm.geometry-dash-odyssey"),
        GYModTile::create("GDUtils", "Jouca & Firee", "gdutilsdevs.gdutils"),
        GYModTile::create("GDPS Hub", "GDPS Hub Team & km7dev", "lblazen.gdps_hub"),
    };

    for (auto& tile : modTiles) {
        contentLayer->addChild(tile);
    }

    auto updateContentSize = [&](CCLayer* layer) {
        float totalHeight = 0.f;

        auto children = layer->getChildren();
        if (children) {
            for (unsigned int i = 0; i < children->count(); ++i) {
                auto node = typeinfo_cast<CCNode*>(children->objectAtIndex(i));
                if (node) {
                    totalHeight += node->getContentSize().height + 10.f;
                }
            }
        }

        layer->setContentSize({ layer->getContentSize().width, totalHeight });
    };

    updateContentSize(contentLayer);

    scroll->m_contentLayer->addChild(contentLayer);

    contentLayer->updateLayout();

    float maxHeight = contentLayer->getContentSize().height;
    scroll->m_contentLayer->setContentSize({
        contentLayer->getContentSize().width,
        maxHeight
    });

    scroll->m_contentLayer->setAnchorPoint({ 0, 1 });
    scroll->m_contentLayer->setPosition({ 0, scroll->getContentSize().height });

    // END OF CONTENT

    updateContentSize(contentLayer);


    CCMenu* leftMenu = CCMenu::create();
    leftMenu->setAnchorPoint({ 0, 0 });
    leftMenu->setContentSize({ 0.f, winSize.height * 0.6f });
    leftMenu->setPosition({ winSize.width * 0.05f, winSize.height * 0.15f });
    leftMenu->setID("left-menu");

    ColumnLayout* leftLayout = ColumnLayout::create();
    leftLayout->setAxis(Axis::Column);
    leftLayout->setGap(10.f);

    leftMenu->setLayout(leftLayout);

    CCMenuItemSpriteExtra* colorBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName(
            "GJ_paintBtn_001.png"
        ),
        this,
        menu_selector(GYSettingSelectLayer::colorPopup)
    );
    colorBtn->setID("color-button");
    leftMenu->addChild(colorBtn);

    auto geodeLoopToggle = CCMenuItemExt::createToggler(
        CCSprite::createWithSpriteFrameName("GJ_fxOnBtn_001.png"),
        CCSprite::createWithSpriteFrameName("GJ_fxOffBtn_001.png"),
        [&](CCMenuItemToggler* toggler) {
            auto fmod = FMODAudioEngine::sharedEngine();
            if (toggler->isOn()) {
                Mod::get()->setSettingValue("menu-loop", false);
            } else {
                Mod::get()->setSettingValue("menu-loop", true);
            }
            fmod->playMusic("menuLoop.mp3", true, 0.5f, 1.0f);
        }
    );
    leftMenu->addChild(geodeLoopToggle);

    CCMenuItemSpriteExtra* settingsBtn = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::create(
            CCSprite::createWithSpriteFrameName("geode.loader/settings.png"),
            CircleBaseColor::DarkPurple,
            CircleBaseSize::Medium
        ),
        this,
        menu_selector(GYSettingSelectLayer::openNormalSettings)
    );
    settingsBtn->setID("settings-button");
    leftMenu->addChild(settingsBtn);

    leftMenu->updateLayout();

    if (Mod::get()->getSavedValue<bool>("settingsBtnClicked") == false) {
        auto settingsLabel = CCSprite::create("settingsLabel.png"_spr);
        settingsLabel->setScale(0.75f);
        settingsLabel->setPosition({ settingsBtn->getPositionX(), settingsBtn->getPositionY() + settingsBtn->getContentSize().height });
        leftMenu->addChild(settingsLabel);
    }

    GYSettingSelectLayer::generateModsList();

    scroll->moveToTop();

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

    if (!jsonData.contains("mods") || !jsonData["mods"].is_object()) {
        log::error("Invalid JSON structure: 'mods' key not found or not an object");
        return false;
    }

    const auto& modsData = jsonData["mods"];
    std::map<std::string, std::pair<std::string, std::string>> modsMap;

    for (auto it = modsData.begin(); it != modsData.end(); ++it) {
        const std::string modID = it.key();
        const auto& modInfo = it.value();

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

            if (modsMap.find(modID) != modsMap.end()) {
                log::info("  - Linked Mod Name: {}, Author: {}", modsMap[modID].first, modsMap[modID].second);
            } else {
                log::warn("  - Mod ID '{}' not found in mods list", modID);
            }
        }
    } else {
        log::warn("No valid 'layers' data found in JSON");
    }

    ScrollLayer* scroll = typeinfo_cast<ScrollLayer*>(this->getChildByID("content-box")->getChildByID("scroll"));
    if (!scroll) {
        log::error("Failed to cast content-box->scroll to ScrollLayer");
        return false;
    }
    scroll->m_contentLayer->updateLayout();

    return true;
}
