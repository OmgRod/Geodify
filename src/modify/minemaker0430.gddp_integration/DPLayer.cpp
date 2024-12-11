#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 


using namespace geode::prelude;
Viper_Hookclass(DPLayer) {
        if (auto bg = this->getChildByID("bg")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-99999);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
}