#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <external-hook-api/HookClass.hpp> 

using namespace geode::prelude;
HookClass(TextureWorkshopLayer) {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
        if (CCSprite* bg = this->getChildByType<CCSprite>(0)) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-2);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
    }
}
