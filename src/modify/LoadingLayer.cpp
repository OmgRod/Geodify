#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;
class $modify(LoadingLayer) { 
    static void onModify(auto& self) {
        (void) self.setHookPriority("LoadingLayer::init", -2); // For SwelvyBGInsert Aka BetterMenu no overlap
    }
    bool init(bool p0) {
        if (!LoadingLayer::init(p0))
            return false;

        if (this->getChildByID("SwelvyBG")) {
            return true;
        }
        if (Mod::get()->getSettingValue<bool>("show-loading")){
            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-3);
            swelvyBG->setID("swelvy-background");
        
            if (CCNode* bg = this->getChildByIDRecursive("bg-texture")) {
                bg->setVisible(false);
            }
        }
        return true;
    }
};