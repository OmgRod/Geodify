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

using namespace geode::prelude;

bool GYModSettingsPopup::setup(std::string const& modName, std::string const& modAuthor, std::string const& modID) {
    this->setTitle(modName + " by " + modAuthor);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto layerSize = CCSize(winSize.width * 0.75f, winSize.height * 0.75f);

    auto scroll = ScrollLayer::create(layerSize * 0.9f - ccp(layerSize.width * 0.05f, layerSize.height * 0.2f));
    scroll->setPosition({ ((winSize.width - layerSize.width) / 2) + layerSize.width * 0.05f, ((winSize.height - layerSize.height) / 2) + layerSize.height * 0.05f });
    scroll->setTouchEnabled(true);

    for (auto& key : Mod::get()->getSettingKeys()) {
        if (key.starts_with(fmt::format("{}/", modID))) {
            SettingNode* node;
            if (auto sett = Mod::get()->getSetting(key)) {
                node = sett->createNode(layerSize.width);
            }
            // else {
            //     node = UnresolvedCustomSettingNode::create(key, Mod::get(), layerSize.width);
            // }
            
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

    this->addChild(scroll);

    return true;
}

GYModSettingsPopup* GYModSettingsPopup::create(std::string const& modName, std::string const& modAuthor, std::string const& modID) {
    auto ret = new GYModSettingsPopup();

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    if (ret->initAnchored(winSize.width * 0.75f, winSize.height * 0.75f, modName, modAuthor, modID, "GJ_square05.png")) {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}