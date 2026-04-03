#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

using namespace geode::prelude;

class GYModSettingsPopup : public geode::Popup {
protected:
    void onApply(CCObject* sender);
    void screenshotPopup(CCObject* sender);
    bool init(std::string const& modName, std::string const& modAuthor, std::string const& modID);
    std::vector<Ref<SettingNode>> m_settings;
public:
    static GYModSettingsPopup* create(std::string const& modName, std::string const& modAuthor, std::string const& modID);
};
