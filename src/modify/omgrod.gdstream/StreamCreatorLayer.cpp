#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 

using namespace geode::prelude;
HookClass(StreamCreatorLayer) {
    if (Mod::get()->getSettingValue<bool>("omgrod.gdstream/StreamCreatorLayer")) {
        if (auto bg = this->getChildByID("menu")->getChildByID("background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-99999);
        
        this->addChild(swelvyBG);
    }
}