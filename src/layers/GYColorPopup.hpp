#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

using namespace geode::prelude;

class GYColorPopup : public geode::Popup</*std::string const&, std::string const&, std::string const&*/> {
protected:
    void onApply(CCObject* sender);
    void screenshotPopup(CCObject* sender);
    bool setup() override;
    std::vector<Ref<SettingNode>> m_settings;
public:
    static GYColorPopup* create();
};
