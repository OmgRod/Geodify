#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include "layers/GYSettingSelectLayer.hpp"

using namespace geode::prelude;

$execute {
    new EventListener<EventFilter<ModPopupUIEvent>>(+[](ModPopupUIEvent* event) {
        if (event->getModID() == Mod::get()->getID()) {
            auto popup = event->getPopup();
            
            if (popup) {
                if (CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(popup->getChildByIDRecursive("settings-button"))) {
                    btn->m_pfnSelector = menu_selector(GYSettingSelectLayer::settingsBtn);
                }
            }
        }
        return ListenerResult::Propagate;
    });
}