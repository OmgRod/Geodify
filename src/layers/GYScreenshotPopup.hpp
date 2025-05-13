#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <string>

#include "../Tags.hpp"

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup<int const&> {
protected:
    Ref<LazySprite> m_sprite;

    bool setup(int const& layer) override;
    void onDownloadFail();

public:
    static GYScreenshotPopup* create(int const& text);
    std::string extractLastSegment(const std::string& input);
};
