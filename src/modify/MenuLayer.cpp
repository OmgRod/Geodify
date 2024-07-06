#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
	static void onModify(auto& self) {
        (void)self.setHookPriority("MenuLayer::init", -2); // For SwelvyBGInsert Aka BetterMenu no overlap
    }
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		if (this->getChildByID("SwelvyBG")) {
			return true;
		}

        if (Mod::get()->getSettingValue<bool>("show-main")){
			if (CCNode* mainmenu = this->getChildByIDRecursive("main-menu-bg")) { 
				mainmenu->setVisible(false); 
			}
			SwelvyBG* swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};