#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <external-hook-api/HookClass.hpp> 
using namespace geode::prelude;
HookClass(GlobedMenuLayer) {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
        if (auto bg = this->getChildByID("background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
    }
}
