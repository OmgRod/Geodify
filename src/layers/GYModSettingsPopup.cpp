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

#include "GYModSettingsPopup.hpp"
#include "GYScreenshotPopup.hpp"
#include "../Tags.hpp"

using namespace geode::prelude;

void GYModSettingsPopup::onApply(CCObject* sender) {
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

void GYModSettingsPopup::screenshotPopup(CCObject* sender) {
    if (auto node = typeinfo_cast<CCNode*>(sender)) {
        GYScreenshotPopup::create(node->getID())->show();
    };
}

bool GYModSettingsPopup::init(std::string_view modName, std::string_view modAuthor, std::string_view modID) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    if (!Popup::init(winSize.width * 0.75f, winSize.height * 0.75f))
            return false;
    
    this->setTitle(std::string(modName) + " by " + std::string(modAuthor));

    auto layerSize = CCSize(winSize.width * 0.75f, winSize.height * 0.9f);

    auto scroll = ScrollLayer::create(layerSize * 0.9f - ccp(layerSize.width * 0.05f, layerSize.height * 0.35f));
    scroll->setPosition({ layerSize.width * 0.05f, layerSize.height * 0.175f });
    scroll->setTouchEnabled(true);
    
    CCScale9Sprite* contentBox = CCScale9Sprite::create("square02b_001.png");
    contentBox->setColor(ccColor3B{0, 0, 0});
    contentBox->setOpacity(60);
    contentBox->setContentSize(scroll->getContentSize());
    contentBox->setPosition(scroll->getPosition());
    contentBox->setAnchorPoint({ 0, 0 });
    contentBox->setID("content-box");
    auto scrollbar = geode::Scrollbar::create(scroll);
    scrollbar->setAnchorPoint({1, 0});
	scrollbar->setPositionX(scroll->getContentWidth() + scrollbar->getContentWidth() + 5);
    contentBox->addChild(scrollbar);
    this->m_mainLayer->addChild(contentBox);

    for (auto& key : Mod::get()->getSettingKeys()) {
        if (key.starts_with(fmt::format("{}/", modID))) {
            SettingNode* node;
            if (auto sett = Mod::get()->getSetting(key)) {
                node = sett->createNode(layerSize.width);
                if (sett->getDescription().has_value()) {
                    auto menu = node->getChildByType<CCMenu*>(0);
                    auto btn = menu->getChildByType<CCMenuItemSpriteExtra*>(0);

                    Tags tags;
                    node->setID(key);
                    btn->setID(key);

                    btn->setTarget(node, menu_selector(GYModSettingsPopup::screenshotPopup));
                }
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
    scroll->m_contentLayer->updateLayout();
    scroll->moveToTop();

    auto menu = CCMenu::create();
    menu->setPosition({ 0.f, 0.f });

    auto applyBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Apply"),
        this,
        menu_selector(GYModSettingsPopup::onApply)
    );
    applyBtn->setPosition({ layerSize.width * 0.5f, layerSize.height * 0.1f });

    menu->addChild(applyBtn);

    this->m_mainLayer->addChild(menu);
    this->m_mainLayer->addChild(scroll);

    return true;
}

GYModSettingsPopup* GYModSettingsPopup::create(std::string_view modName, std::string_view modAuthor, std::string_view modID) {
    auto ret = new GYModSettingsPopup();

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    if (ret->init(modName, modAuthor, modID)) {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}