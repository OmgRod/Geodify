#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 

using namespace geode::prelude;
HookClass(BetterAchievementLayer) {
    if (Mod::get()->getSettingValue<bool>("limegradient.betterachievements/BetterAchievementLayer")) {
        if (auto bg = this->getChildByID("content-background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        
        this->addChild(swelvyBG);
    }
}


