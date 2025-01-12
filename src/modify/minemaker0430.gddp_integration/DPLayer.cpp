#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 


using namespace geode::prelude;
HookClass(DPLayer) {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
        if (auto bg = this->getChildByID("bg")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-99999);
        
        this->addChild(swelvyBG);
    }
}