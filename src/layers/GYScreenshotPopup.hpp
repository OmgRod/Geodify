#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <string>

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup {
protected:
    Ref<LazySprite> m_sprite;

    bool init(int const& layer);
    void onDownloadFail();

public:
    static GYScreenshotPopup* create(int const& text);
    std::string extractLastSegment(const std::string& input);
};
