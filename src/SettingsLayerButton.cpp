#include <Geode/loader/SettingV3.hpp>
#include <Geode/loader/Mod.hpp>
#include "layers/GYSettingSelectLayer.hpp"

using namespace geode::prelude;

// Code from Geode SDK (thanks guys!)
$on_mod(Loaded) {
    ButtonSettingPressedEventV3(Mod::get(), "settings-button").listen([] (auto buttonKey) {
        if (buttonKey == "open") {
            // preventing that one playLayer bug
            if (!PlayLayer::get()) {
                auto scene = GYSettingSelectLayer::scene();
                auto transition = CCTransitionFade::create(0.5f, scene);
                CCDirector::sharedDirector()->pushScene(transition);
            } else {
                GYSettingSelectLayer::popup()->show();
            };
        }
    }).leak();
}
