#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <string>

using namespace geode::prelude;

class GeodifyScreenshotPopup : public FLAlertLayer {
public:
    static GeodifyScreenshotPopup* create(const std::string& title, CCSprite* screenshot) {
        GeodifyScreenshotPopup* ret = new GeodifyScreenshotPopup();
        if (ret && ret->init(title, screenshot)) {
            ret->autorelease();
            return ret;
        } else {
            delete ret;
            return nullptr;
        }
    }
};