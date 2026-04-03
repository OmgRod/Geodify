#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

using namespace geode::prelude;

class GYColorPopup : public geode::Popup {
protected:
    void onApply(CCObject* sender);
    void screenshotPopup(CCObject* sender);
    bool init();
    std::vector<Ref<SettingNode>> m_settings;
public:
    static GYColorPopup* create();
};
