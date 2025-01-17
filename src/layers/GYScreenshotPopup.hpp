#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <string>

#include "Tags.hpp"

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup<int const&> {
protected:
    bool setup(int const& layer) override {
        Tags tags;
        auto layerName = tags.getStringFromTag(layer);

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        this->setTitle(layerName);
        m_mainLayer->setContentSize({ winSize.width * 0.6f, winSize.height * 0.7f });
        m_mainLayer->updateLayout();

        auto sprite = CCSprite::createWithSpriteFrameName(fmt::format("{}Preview.png"_spr, layerName).c_str());
        log::debug("Loading sprite: {}", fmt::format("omgrod.geodify/{}Preview.png", layerName));

        // Calculate the maximum allowed dimensions for the sprite
        auto maxWidth = m_mainLayer->getContentSize().width * 0.75f;
        auto maxHeight = m_mainLayer->getContentSize().height * 0.75f;

        // Get the sprite's original dimensions
        auto spriteWidth = sprite->getContentSize().width;
        auto spriteHeight = sprite->getContentSize().height;

        // Calculate the scale factor to maintain the aspect ratio
        float scale = std::min(maxWidth / spriteWidth, maxHeight / spriteHeight);

        // Set the sprite's scale
        sprite->setScale(scale);

        // Add the sprite to the main layer at the center
        m_mainLayer->addChildAtPosition(sprite, Anchor::Center);

        return true;
    }

public:
    static GYScreenshotPopup* create(int const& text) {
        auto ret = new GYScreenshotPopup();
        if (ret->initAnchored(240.f, 160.f, text)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }
};
