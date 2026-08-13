#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

using namespace geode::prelude;

class GYModSettingsPopup : public geode::Popup {
protected:
    void onApply(CCObject* sender);
    void screenshotPopup(CCObject* sender);
    bool init(std::string_view modName, std::string_view modAuthor, std::string_view modID);
    std::vector<Ref<SettingNode>> m_settings;
public:
    static GYModSettingsPopup* create(std::string_view modName, std::string_view modAuthor, std::string_view modID);
};
