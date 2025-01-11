#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <external-hook-api/include/HookClass.hpp> 

using namespace geode::prelude;
HookClass(IDListLayer) {
        if (auto bg = this->getChildByType<CCSprite>(0)) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
}