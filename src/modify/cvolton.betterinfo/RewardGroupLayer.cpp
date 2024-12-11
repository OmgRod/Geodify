#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 
using namespace geode::prelude;
Viper_Hookclass(RewardGroupLayer) {
        if (auto bg = this->getChildByID("cvolton.betterinfo/background")) {
            bg->setVisible(false);
        }
        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
}