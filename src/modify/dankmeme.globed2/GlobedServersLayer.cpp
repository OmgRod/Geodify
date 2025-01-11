#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 
using namespace geode::prelude;
HookClass(GlobedServersLayer) {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
        if (CCNode* bg = typeinfo_cast<CCNode*>(this->getChildren()->objectAtIndex(1))) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
    }
}