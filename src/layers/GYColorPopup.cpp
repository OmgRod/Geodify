#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include <Geode/binding/ButtonSprite.hpp>
#include <Geode/loader/Mod.hpp>
#include <Geode/loader/ModSettingsManager.hpp>
#include <Geode/ui/ScrollLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <Geode/ui/General.hpp>
#include <Geode/ui/Scrollbar.hpp>
#include <Geode/loader/Setting.hpp>

#include "GYColorPopup.hpp"

using namespace geode::prelude;

void GYColorPopup::onApply(CCObject* sender) {
    bool someChangesMade = false;
    for (auto& sett : m_settings) {
        if (sett->hasUncommittedChanges()) {
            sett->commit();
            someChangesMade = true;
        }
    }
    if (!someChangesMade) {
        FLAlertLayer::create("Info", "No changes have been made.", "OK")->show();
    }
}

bool GYColorPopup::setup() {
    this->setTitle("Color Settings");

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto layerSize = CCSize(winSize.width * 0.75f, winSize.height * 0.75f);

    auto scroll = ScrollLayer::create(layerSize * 0.9f - ccp(layerSize.width * 0.05f, layerSize.height * 0.5f));
    scroll->setPosition({ layerSize.width * 0.05f, layerSize.height * 0.375f });
    scroll->setTouchEnabled(true);

    for (auto& key : Mod::get()->getSettingKeys()) {
        if (key.starts_with("color-")) {
            SettingNode* node;
            if (auto sett = Mod::get()->getSetting(key)) {
                node = sett->createNode(layerSize.width);
            }
            // else {
            //     node = UnresolvedCustomSettingNode::create(key, Mod::get(), layerSize.width);
            // }
            
            m_settings.push_back(node);
            scroll->m_contentLayer->addChild(node);
        }
    }
    scroll->m_contentLayer->setLayout(
        ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAutoGrowAxis(scroll->getContentHeight())
            ->setCrossAxisOverflow(false)
            ->setAxisAlignment(AxisAlignment::End)
            ->setGap(0)
    );
    scroll->moveToTop();

    auto menu = CCMenu::create();
    menu->setPosition({ 0.f, 0.f });

    auto applyBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Apply"),
        this,
        menu_selector(GYColorPopup::onApply)
    );
    applyBtn->setPosition({ layerSize.width * 0.5f, layerSize.height * 0.1f });

    menu->addChild(applyBtn);

    this->m_mainLayer->addChild(menu);
    this->m_mainLayer->addChild(scroll);

    return true;
}

GYColorPopup* GYColorPopup::create() {
    auto ret = new GYColorPopup();

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    if (ret->initAnchored(winSize.width * 0.75f, winSize.height * 0.75f, "GJ_square01.png")) {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}