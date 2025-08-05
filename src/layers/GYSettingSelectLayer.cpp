#include <Geode/Geode.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/loader/Loader.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>

#include "GYSettingSelectLayer.hpp"
#include "GYColorPopup.hpp"
#include "GYModTile.hpp"
#include "../SwelvyBG.hpp"

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
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, GYSettingSelectLayer::scene()));
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

    // Mods data
    std::vector<std::tuple<std::string, std::string, std::string>> modData = {
        { "Geometry Dash", "RobTop", "gd" },
        { "Geode", "Geode Team", "geode.loader" },
        { "BetterInfo", "Cvolton", "cvolton.betterinfo" },
        { "Globed", "dankmeme", "dankmeme.globed2" },
        { "Texture Loader", "Geode Team", "geode.texture-loader" },
        { "Integrated Demonlist", "hiimjustin000", "hiimjustin000.integrated_demonlist" },
        { "GDPS Switcher", "km7dev", "km7dev.gdps-switcher" },
        { "BetterAchievements", "limegradient", "limegradient.betterachievements" },
        { "GDDP Integration", "Minemaker0430", "minemaker0430.gddp_integration" },
        { "Garage Plus", "OmgRod", "omgrod.garage_plus" },
        { "GDStream", "OmgRod", "omgrod.gdstream" },
        { "Geodify", "OmgRod & Cosmella-v", "omgrod.geodify" },
        { "Newgrounds Explorer", "TheSillyDoggo", "thesillydoggo.newgrounds_explorer" },
        { "Texture Workshop", "Uproxide", "uproxide.textures" },
        { "Geometry Dash: Odyssey", "chumiu", "teamtcm.geometry-dash-odyssey" },
        { "GDUtils", "Jouca & Firee", "gdutilsdevs.gdutils" },
        { "GDPS Hub", "GDPS Hub Team + 2 more", "lblazen.gdps_hub" },
        { "GDCP List Integration", "GDCP Team + 2 more", "gdcpteam.challenge-list" },
        { "Random Tab", "Alphalaneous", "alphalaneous.random_tab" },
        { "Geometry Dash: Surge", "OmgRod", "omgrod.geometry-dash-surge" },
    };

    for (const auto& [name, author, id] : modData) {
        if (Loader::get()->isModLoaded(id) || id == "gd") {
            contentLayer->addChild(GYModTile::create(name, author, id));
        }
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

    // auto geodeLoopToggle = CCMenuItemExt::createToggler(
    //     CCSprite::createWithSpriteFrameName("GJ_fxOnBtn_001.png"),
    //     CCSprite::createWithSpriteFrameName("GJ_fxOffBtn_001.png"),
    //     [&](CCMenuItemToggler* toggler) {
    //         auto fmod = FMODAudioEngine::sharedEngine();
    //         if (toggler->isOn()) {
    //             Mod::get()->setSettingValue("menu-loop", false);
    //         } else {
    //             Mod::get()->setSettingValue("menu-loop", true);
    //         }
    //         fmod->playMusic("menuLoop.mp3", true, 0.5f, 1.0f);
    //     }
    // );
    // leftMenu->addChild(geodeLoopToggle);

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

    scroll->moveToTop();

    this->addChild(leftMenu);
    this->addChild(menu);
    
    return true;
}