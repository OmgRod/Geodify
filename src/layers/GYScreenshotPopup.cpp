#include "GYScreenshotPopup.hpp"
#include "../Tags.hpp"

bool GYScreenshotPopup::init(std::string_view layerName) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    if (!Popup::init(winSize.width * .6f, winSize.height * .7f)) return false;

    Tags tags;

    if (layerName.empty()) {
        log::error("Layer name is empty for: {}", layerName);
        return false;
    }

    m_layerName = layerName;

    std::string_view result = extractLastSegment(layerName);

    if (!m_mainLayer) {
        log::error("m_mainLayer is not initialized");
        return false;
    }

    this->setTitle(std::string(result));

    m_mainLayer->setContentSize({
        winSize.width * 0.6f,
        winSize.height * 0.7f
    });

    m_mainLayer->updateLayout();

    CCSize spriteTargetSize{
        m_mainLayer->getContentSize().width * 0.75f,
        m_mainLayer->getContentSize().height * 0.75f
    };

    m_spriteTargetSize = spriteTargetSize;

    m_sprite = LazySprite::create(spriteTargetSize);
    m_sprite->setAutoResize(true);

    m_sprite->setLoadCallback([this, spriteTargetSize](Result<> res) {
        if (res) {
            log::info("Preview loaded successfully");
            createToggleButtons();
        } else {
            log::error(
                "Failed to load preview: {}",
                res.unwrapErr()
            );

            removeToggleButtons();
            onDownloadFail();

            auto sprite = LazySprite::create(spriteTargetSize);
            sprite->setAutoResize(true);
            sprite->loadFromFile(
                Mod::get()->getResourcesDir() / "noPreview.png"
            );

            sprite->setPosition(this->m_sprite->getPosition());
            this->m_mainLayer->addChild(sprite);

            auto reportSpr = ButtonSprite::create("Report Bug");
            reportSpr->setScale(0.75f);

            auto reportBtn = CCMenuItemExt::createSpriteExtra(
                reportSpr,
                [](CCObject*) {
                    geode::utils::web::openLinkInBrowser("https://github.com/OmgRod/Geodify/issues/new?template=bug_report.md");
                }
            );

            reportBtn->setPosition({
                this->m_buttonMenu->getContentWidth() / 2,
                this->m_buttonMenu->getContentHeight() * 0.1f
            });
            
            this->m_buttonMenu->addChild(reportBtn);

            m_sprite->removeFromParentAndCleanup(true);
            m_sprite = nullptr;
        }
    });

    m_mainLayer->addChildAtPosition(
        m_sprite,
        Anchor::Center
    );

    reloadPreview();

    return true;
}

std::string GYScreenshotPopup::getPreviewURL() {
    if (m_previewType == PreviewType::Sapphire) {
        return fmt::format(
            "https://raw.githubusercontent.com/OmgRod/Geodify/master/previews/sapphire/{}Preview.png",
            m_layerName
        );
    }

    return fmt::format(
        "https://raw.githubusercontent.com/OmgRod/Geodify/master/previews/{}Preview.png",
        m_layerName
    );
}

void GYScreenshotPopup::reloadPreview() {
    auto url = getPreviewURL();

    //log::info("Loading preview: {}", url);

    if (m_sprite) {
        m_sprite->removeFromParentAndCleanup(true);
        m_sprite = nullptr;
    }

    m_sprite = LazySprite::create(m_spriteTargetSize);
    m_sprite->setAutoResize(true);

    m_sprite->setLoadCallback([this](Result<> res) {
        if (res) {
            //log::info("Preview loaded successfully");

            fixSpriteSize();

            createToggleButtons();
        } else {
            log::error(
                "Failed to load preview: {}",
                res.unwrapErr()
            );

            removeToggleButtons();
            createReportButton();
            onDownloadFail();
        }
    });

    m_mainLayer->addChildAtPosition(
        m_sprite,
        Anchor::Center
    );

    m_sprite->loadFromUrl(url);
}

void GYScreenshotPopup::onDownloadFail() {
    if (!m_sprite) return;

    m_sprite->removeFromParentAndCleanup(true);

    m_sprite = LazySprite::create(m_spriteTargetSize);
    m_sprite->setAutoResize(true);

    m_mainLayer->addChildAtPosition(
        m_sprite,
        Anchor::Center
    );

    m_sprite->loadFromFile(
        Mod::get()->getResourcesDir() / "noPreview.png"
    );

    fixSpriteSize();
}


std::string_view GYScreenshotPopup::extractLastSegment(std::string_view input) {
    const auto lastSlash = input.rfind('/');

    if (lastSlash != std::string_view::npos) {
        return input.substr(lastSlash + 1);
    }

    return input;
}


GYScreenshotPopup* GYScreenshotPopup::create(std::string_view text) {
    auto ret = new GYScreenshotPopup();

    if (ret->init(text)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

void GYScreenshotPopup::createToggleButtons() {
    if (m_swelvyBtn || m_sapphireBtn)
        return;

    auto swelvySpr = ButtonSprite::create("SwelvyBG");
    swelvySpr->setScale(0.65f);

    m_swelvyBtn = CCMenuItemExt::createSpriteExtra(
        swelvySpr,
        [this](CCObject*) {
            m_previewType = PreviewType::SwelvyBG;
            reloadPreview();
        }
    );


    auto sapphireSpr = ButtonSprite::create("Sapphire");
    sapphireSpr->setScale(0.65f);

    m_sapphireBtn = CCMenuItemExt::createSpriteExtra(
        sapphireSpr,
        [this](CCObject*) {
            m_previewType = PreviewType::Sapphire;
            reloadPreview();
        }
    );


    m_swelvyBtn->setPosition({
        m_buttonMenu->getContentWidth() * 0.3f,
        m_buttonMenu->getContentHeight() * 0.1f
    });


    m_sapphireBtn->setPosition({
        m_buttonMenu->getContentWidth() * 0.7f,
        m_buttonMenu->getContentHeight() * 0.1f
    });


    m_buttonMenu->addChild(m_swelvyBtn);
    m_buttonMenu->addChild(m_sapphireBtn);
}


void GYScreenshotPopup::removeToggleButtons() {
    if (m_swelvyBtn) {
        m_swelvyBtn->removeFromParentAndCleanup(true);
        m_swelvyBtn = nullptr;
    }

    if (m_sapphireBtn) {
        m_sapphireBtn->removeFromParentAndCleanup(true);
        m_sapphireBtn = nullptr;
    }
}

void GYScreenshotPopup::fixSpriteSize() {
    if (!m_sprite) return;

    auto size = m_sprite->getContentSize();

    if (size.width == 0 || size.height == 0) return;

    float scaleX = m_spriteTargetSize.width / size.width;
    float scaleY = m_spriteTargetSize.height / size.height;

    m_sprite->setScale(std::min(scaleX, scaleY));
}

void GYScreenshotPopup::createReportButton() {
    auto reportSpr = ButtonSprite::create("Report Bug");
    reportSpr->setScale(0.75f);

    auto reportBtn = CCMenuItemExt::createSpriteExtra(
        reportSpr,
        [](CCObject*) {
            geode::utils::web::openLinkInBrowser(
                "https://github.com/OmgRod/Geodify/issues/new?template=bug_report.md"
            );
        }
    );

    reportBtn->setPosition({
        m_buttonMenu->getContentWidth() / 2,
        m_buttonMenu->getContentHeight() * 0.1f
    });

    m_buttonMenu->addChild(reportBtn);
}
