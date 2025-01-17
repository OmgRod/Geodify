#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 
using namespace geode::prelude;
HookClass(GlobedSettingsLayer) {
    if (Mod::get()->getSettingValue<bool>("dankmeme.globed2/GlobedSettingsLayer")) {
        if (auto bg = this->getChildByID("background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        
        this->addChild(swelvyBG);
    }
}