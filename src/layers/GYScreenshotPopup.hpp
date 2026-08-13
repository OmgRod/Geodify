#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <string>

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup {
protected:
    Ref<LazySprite> m_sprite;

    std::string m_layerName;

    enum class PreviewType {
        SwelvyBG,
        Sapphire
    };

    PreviewType m_previewType = PreviewType::SwelvyBG;

    std::string getPreviewURL();
    void reloadPreview();

    bool init(std::string_view layer);
    void onDownloadFail();

    Ref<CCMenuItemSpriteExtra> m_swelvyBtn;
    Ref<CCMenuItemSpriteExtra> m_sapphireBtn;

    CCSize m_spriteTargetSize;

    void createToggleButtons();
    void removeToggleButtons();
    void fixSpriteSize();
    void createReportButton();

public:
    static GYScreenshotPopup* create(std::string_view text);
    std::string_view extractLastSegment(std::string_view input);
};
