#include "GYScreenshotPopup.hpp"

bool GYScreenshotPopup::setup(int const& layer) {
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

    std::string URL = fmt::format("https://raw.githubusercontent.com/OmgRod/Geodify/master/previews/{}Preview.png", layerName);

    auto req = web::WebRequest();
    m_downloadListener.bind([this](web::WebTask::Event* e) {
        if (auto res = e->getValue()) {
            if (!res->ok()) {
                log::error("Failed to download image from URL.");
                onDownloadFail();
            } else {
                auto data = res->data();
                std::thread imageThread = std::thread([data, this]() {
                    m_image = new CCImage();
                    m_image->autorelease();
                    m_image->initWithImageData(const_cast<uint8_t*>(data.data()), data.size());
                    geode::Loader::get()->queueInMainThread([this]() {
                        imageCreationFinished(m_image);
                    });
                });
                imageThread.detach();
            }
        }
    });
    m_downloadListener.setFilter(req.get(URL));

    return true;
}

void GYScreenshotPopup::imageCreationFinished(CCImage* image) {
    CCTexture2D* texture = new CCTexture2D();
    texture->autorelease();
    texture->initWithImage(image);

    m_sprite = CCSprite::createWithTexture(texture);
    if (m_sprite) {
        auto maxWidth = m_mainLayer->getContentSize().width * 0.75f;
        auto maxHeight = m_mainLayer->getContentSize().height * 0.75f;

        auto spriteWidth = m_sprite->getContentSize().width;
        auto spriteHeight = m_sprite->getContentSize().height;

        float scale = std::min(maxWidth / spriteWidth, maxHeight / spriteHeight);
        m_sprite->setScale(scale);

        m_mainLayer->addChildAtPosition(m_sprite, Anchor::Center);
    }
}

void GYScreenshotPopup::onDownloadFail() {
    CCSprite* fallbackSprite = CCSprite::create("noPreview.png"_spr);
    if (fallbackSprite) {
        auto maxWidth = m_mainLayer->getContentSize().width * 0.75f;
        auto maxHeight = m_mainLayer->getContentSize().height * 0.75f;

        auto spriteWidth = fallbackSprite->getContentSize().width;
        auto spriteHeight = fallbackSprite->getContentSize().height;

        float scale = std::min(maxWidth / spriteWidth, maxHeight / spriteHeight);
        fallbackSprite->setScale(scale);

        m_mainLayer->addChildAtPosition(fallbackSprite, Anchor::Center);
    }
}

std::string GYScreenshotPopup::extractLastSegment(const std::string& input) {
    size_t lastDash = input.rfind('-');
    if (lastDash != std::string::npos) {
        return input.substr(lastDash + 1);
    }
    return input;
}

GYScreenshotPopup* GYScreenshotPopup::create(int const& text) {
    auto ret = new GYScreenshotPopup();
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    if (ret->initAnchored(winSize.width * .6f, winSize.height * .7f, text)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}