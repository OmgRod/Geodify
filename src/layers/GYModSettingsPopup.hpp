#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

using namespace geode::prelude;

class GYModSettingsPopup : public geode::Popup<std::string const&, std::string const&, std::string const&> {
protected:
    void screenshotPopup(CCObject* sender);
    bool setup(std::string const& modName, std::string const& modAuthor, std::string const& modID) override;

public:
    static GYModSettingsPopup* create(std::string const& modName, std::string const& modAuthor, std::string const& modID);
};
