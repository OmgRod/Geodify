#include <Geode/Geode.hpp>
#include <Geode/loader/Loader.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp>

using namespace geode::prelude;

HookClass(ModsLayer) {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
        if (!(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme"))) {
            if (auto bg = this->getChildByID("bg")) {
                bg->setVisible(false);
            }

            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-1);
            
            this->addChild(swelvyBG);
        }
    }
}


