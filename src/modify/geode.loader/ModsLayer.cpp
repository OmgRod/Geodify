#include <Geode/Geode.hpp>
#include <Geode/loader/Loader.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp"

using namespace geode::prelude;

Viper_Hookclass(ModsLayer) {
        if (!(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme"))) {
            if (auto bg = this->getChildByID("bg")) {
                bg->setVisible(false);
            }

            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-1);
            swelvyBG->setID("swelvy-background");
            this->addChild(swelvyBG);
        }
}


