#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 

using namespace geode::prelude;
Viper_Hookclass(TextureWorkshopLayer) {
        if (CCSprite* bg = this->getChildByType<CCSprite>(0)) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-2);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
}
