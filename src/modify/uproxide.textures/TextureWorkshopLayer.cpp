#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp> 

using namespace geode::prelude;
HookClass(TextureWorkshopLayer) {
    if (Mod::get()->getSettingValue<bool>("uproxide.textures/TextureWorkshopLayer")) {
        if (CCSprite* bg = this->getChildByType<CCSprite>(0)) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-2);
        
        this->addChild(swelvyBG);
    }
}
