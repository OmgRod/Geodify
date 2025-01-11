#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>
#include "layers/GYSettingSelectLayer.hpp"

using namespace geode::prelude;

$execute {
    new EventListener<EventFilter<ModPopupUIEvent>>(+[](ModPopupUIEvent* event) {
        if (event->getModID() == "omgrod.geodify") {
            auto popup = event->getPopup();
            
            if (popup) {
                if (CCMenuItemSpriteExtra* btn = typeinfo_cast<CCMenuItemSpriteExtra*>(popup->getChildByIDRecursive("settings-button"))) {
                    btn->m_pfnSelector = menu_selector(GYSettingSelectLayer::settingsBtn); // this code sucks - it keeps crashing. im sorry if creating a fake button is a bit too much
                    
                    // CCSprite* settings = CCSprite::create("geode.loader/settings.png");
                    // CircleButtonSprite* settingsBtn = nullptr;

                    // if (Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme")) {
                    //     settingsBtn = CircleButtonSprite::create(settings, CircleBaseColor::DarkPurple, CircleBaseSize::SmallAlt);
                    // } else {
                    //     settingsBtn = CircleButtonSprite::create(settings, CircleBaseColor::Green, CircleBaseSize::SmallAlt);
                    // }

                    // btn->setVisible(false);

                    // auto newBtn = CCMenuItemSpriteExtra::create(settingsBtn, nullptr, );
                    // newBtn->setID("settings-button-geodify");
                    // newBtn->setPosition(btn->getPosition());
                    // newBtn->setAnchorPoint(btn->getAnchorPoint());
                    // newBtn->setScale(btn->getScale());
                    // btn->getParent()->addChild(newBtn);
                }
            }
        }
        return ListenerResult::Propagate;
    });
}