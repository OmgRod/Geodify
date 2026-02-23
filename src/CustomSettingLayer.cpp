#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include "layers/GYSettingSelectLayer.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    auto listener = ModPopupUIEvent().listen([](FLAlertLayer* popup, std::string_view, std::optional<Mod*> mod) {
        if (mod && mod.value()->getID() == Mod::get()->getID()) {
            if (popup) {
                if (CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(popup->getChildByIDRecursive("settings-button"))) {
                    btn->m_pfnSelector = menu_selector(GYSettingSelectLayer::settingsBtn);
                }
            }
        }
        return ListenerResult::Propagate;
    });
}