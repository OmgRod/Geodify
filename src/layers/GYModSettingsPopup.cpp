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

bool GYModSettingsPopup::setup(std::string const& modName, std::string const& modAuthor) {
    this->setTitle(modName + " by " + modAuthor);

    auto layerSize = this->m_obContentSize;

    auto scroll = ScrollLayer::create(layerSize - ccp(0, layerSize.height * 0.1f));
    scroll->setTouchEnabled(true);

    for (auto& key : Mod::get()->getSettingKeys()) {
        SettingNode* node;
        if (auto sett = Mod::get()->getSetting(key)) {
            node = sett->createNode(layerSize.width);
        }
        // else {
        //     node = UnresolvedCustomSettingNode::create(key, Mod::get(), layerSize.width);
        // }

        scroll->m_contentLayer->addChild(node);
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

GYModSettingsPopup* GYModSettingsPopup::create(std::string const& modName, std::string const& modAuthor) {
    auto ret = new GYModSettingsPopup();

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    
    if (ret->initAnchored(winSize.width * 0.75f, winSize.height * 0.75f, modName, modAuthor, "GJ_square05.png")) {
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;
}