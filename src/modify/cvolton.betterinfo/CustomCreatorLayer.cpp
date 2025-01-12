#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <HookClass.hpp>
using namespace geode::prelude;

HookClass_Scene(cvolton_betterinfo_CustomCreatorLayer,"cvolton.betterinfo/CustomCreatorLayer") {
    if (Mod::get()->getSettingValue<bool>("external-mods")) {
         if (auto bg = _This->getChildByID("cvolton.betterinfo/background")) {
            bg->setVisible(false);
            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-1);
            
            _This->addChild(swelvyBG);
        }
    }
}