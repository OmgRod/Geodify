#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/binding/LoadingCircle.hpp>
#include <string>
#include "../Tags.hpp"
#include "../ImageCache.hpp"

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup<int const&> {
protected:
    CCClippingNode* m_clippingNode;
    LoadingCircle* m_loadingCircle;
    CCImage* m_image;
    int m_layerID;
    geode::EventListener<web::WebTask> m_downloadListener;

    bool setup(int const& layer) override {
        Tags tags;
        auto layerName = tags.getStringFromTag(layer);

        if (layerName.empty()) {
            log::error("Layer name is empty for tag: {}", layer);
            return false;
        }

        std::string result = extractLastSegment(layerName);
        m_layerID = layer;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        if (!m_mainLayer) {
            log::error("m_mainLayer is not initialized");
            return false;
        }

        this->setTitle(result);
        m_mainLayer->setContentSize({ winSize.width * 0.6f, winSize.height * 0.7f });
        m_mainLayer->updateLayout();

        // Create a border
        auto border = CCScale9Sprite::create("GJ_square07.png");
        border->setContentSize(m_mainLayer->getContentSize());
        border->setPosition(m_mainLayer->getContentSize() / 2);
        border->setZOrder(2);
        m_mainLayer->addChild(border);

        // Create a mask for clipping
        auto mask = CCLayerColor::create({255, 255, 255});
        mask->setContentSize({391, 220});
        mask->setPosition({m_mainLayer->getContentSize().width / 2 - 391 / 2, m_mainLayer->getContentSize().height / 2 - 220 / 2});

        // Create a clipping node
        m_clippingNode = CCClippingNode::create();
        m_clippingNode->setContentSize(m_mainLayer->getContentSize());
        m_clippingNode->setStencil(mask);
        m_clippingNode->setZOrder(1);
        m_mainLayer->addChild(m_clippingNode);

        // Initialize and show the loading circle
        m_loadingCircle = LoadingCircle::create();
        m_loadingCircle->setPosition(m_mainLayer->getContentSize() / 2);
        m_loadingCircle->setScale(1.0f);
        m_loadingCircle->show();
        m_mainLayer->addChild(m_loadingCircle);

        // Check if the image is already cached
        if (CCImage* image = ImageCache::get()->getImage(fmt::format("thumb-{}", m_layerID))) {
            m_image = image;
            m_loadingCircle->removeFromParent();
            imageCreationFinished(m_image);
            return true;
        }

        // Download the image
        std::string URL = fmt::format("https://raw.githubusercontent.com/OmgRod/Geodify/refs/heads/master/res/previews/{}Preview.png", layerName);
        auto req = web::WebRequest();
        auto downloadTask = req.get(URL);
        m_downloadListener.bind([this](web::WebTask::Event* e) {
            if (auto res = e->getValue()) {
                if (!res->ok()) {
                    onDownloadFail();
                } else {
                    auto data = res->data();
                    std::thread imageThread = std::thread([data, this]() {
                        m_image = new CCImage();
                        m_image->autorelease();
                        m_image->initWithImageData(const_cast<uint8_t*>(data.data()), data.size());
                        geode::Loader::get()->queueInMainThread([this]() {
                            ImageCache::get()->addImage(m_image, fmt::format("thumb-{}", m_layerID));
                            imageCreationFinished(m_image);
                        });
                    });
                    imageThread.detach();
                }
            }
        });
        m_downloadListener.setFilter(downloadTask);

        return true;
    }

    void imageCreationFinished(CCImage* image) {
        auto texture = new CCTexture2D();
        texture->autorelease();
        texture->initWithImage(image);
        onDownloadFinished(CCSprite::createWithTexture(texture));
    }

    void onDownloadFinished(CCSprite* image) {
        float maxHeight = m_mainLayer->getContentSize().height * 0.75f;
        float scale = maxHeight / image->getContentSize().height;
        image->setScale(scale);
        image->setPosition(m_mainLayer->getContentSize() / 2);
        m_clippingNode->addChild(image);
        if (m_loadingCircle) {
            m_loadingCircle->removeFromParent();
        }
    }

    void onDownloadFail() {
        auto image = CCSprite::create("noThumb.png");
        float maxHeight = m_mainLayer->getContentSize().height * 0.75f;
        float scale = maxHeight / image->getContentSize().height;
        image->setScale(scale);
        image->setPosition(m_mainLayer->getContentSize() / 2);
        m_clippingNode->addChild(image);
        if (m_loadingCircle) {
            m_loadingCircle->removeFromParent();
        }
    }

public:
    struct Fields {
        EventListener<web::WebTask> m_listener;
    };

    std::string extractLastSegment(const std::string& input) {
        size_t lastDash = input.rfind('-');
        if (lastDash != std::string::npos) {
            return input.substr(lastDash + 1);
        }
        return input;
    }

    static GYScreenshotPopup* create(int const& layer) {
        auto ret = new GYScreenshotPopup();
        if (ret->initAnchored(395, 225, layer)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};
