#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include "layers/GYSettingSelectLayer.hpp"

using namespace geode::prelude;

$on_mod(Loaded) {
    ModPopupUIEvent().listen([](FLAlertLayer* popup, std::string_view, std::optional<Mod*> mod) {
        log::debug("geodify popup event is being received");

        if (!mod.has_value()) {
            log::warn("geodify mod is not provided, using fallback");
            mod = Mod::get();
        }

        auto* modPtr = mod.value();
        if (!modPtr) {
            log::error("geodify mod pointer is null");
            return ListenerResult::Propagate;
        }

        if (modPtr->getID() != Mod::get()->getID()) {
            log::error("geodify mod ID does not match");
            return ListenerResult::Propagate;
        }

        log::debug("geodify mod verified");

        if (!popup) {
            log::error("geodify popup is null");
            return ListenerResult::Propagate;
        }

        log::debug("geodify popup verified");

        auto* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(popup->getChildByIDRecursive("settings-button"));
        if (!btn) {
            log::error("geodify button not found");
            return ListenerResult::Propagate;
        }

        log::debug("geodify button found");
        btn->m_pfnSelector = menu_selector(GYSettingSelectLayer::settingsBtn);

        return ListenerResult::Propagate;
    }).leak();
}
