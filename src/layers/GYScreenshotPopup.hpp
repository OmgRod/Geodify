#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/utils/web.hpp>
#include <string>

#include "../Tags.hpp"

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup<int const&> {
protected:
    EventListener<web::WebTask> m_downloadListener;
    Ref<CCImage> m_image;
    CCSprite* m_sprite;

    bool setup(int const& layer) override;
    void imageCreationFinished(CCImage* image);
    void onDownloadFail();

public:
    static GYScreenshotPopup* create(int const& text);
    std::string extractLastSegment(const std::string& input);
};