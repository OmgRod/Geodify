#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <string>

#include "../Tags.hpp"

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup<int const&> {
protected:
    bool setup(int const& layer) override {
        Tags tags;
        auto layerName = tags.getStringFromTag(layer);

        if (layerName.empty()) {
            log::error("Layer name is empty for tag: {}", layer);
            return false;
        }

        std::string result = extractLastSegment(layerName);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        if (!m_mainLayer) {
            log::error("m_mainLayer is not initialized");
            return false;
        }

        this->setTitle(result);
        m_mainLayer->setContentSize({ winSize.width * 0.6f, winSize.height * 0.7f });
        m_mainLayer->updateLayout();

        /*auto sprite = CCSprite::createWithSpriteFrameName(fmt::format("{}Preview.png"_spr, layerName).c_str());
        if (!sprite) {
            log::error("Sprite not found for frame: {}", fmt::format("{}Preview.png", layerName));
            return false;
        }

        log::debug("Loading sprite: {}", fmt::format("omgrod.geodify/{}Preview.png", layerName));

        auto maxWidth = m_mainLayer->getContentSize().width * 0.75f;
        auto maxHeight = m_mainLayer->getContentSize().height * 0.75f;

        auto spriteWidth = sprite->getContentSize().width;
        auto spriteHeight = sprite->getContentSize().height;

        float scale = std::min(maxWidth / spriteWidth, maxHeight / spriteHeight);
        sprite->setScale(scale);

        m_mainLayer->addChildAtPosition(sprite, Anchor::Center);*/

        auto warning = CCLabelBMFont::create("This feature is not yet implemented. Check back later.", "bigFont.fnt");
        warning->setPosition({ winSize.width * .3f, winSize.height * .35f });
        warning->setScale(0.3f);

        m_mainLayer->addChild(warning);

        return true;
    }

public:
    std::string extractLastSegment(const std::string& input) {
        size_t lastDash = input.rfind('-');
        if (lastDash != std::string::npos) {
            return input.substr(lastDash + 1);
        }
        return input;
    }
    static GYScreenshotPopup* create(int const& text) {
        auto ret = new GYScreenshotPopup();
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        if (ret->initAnchored(winSize.width * .6f, winSize.height * .7f, text)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};
