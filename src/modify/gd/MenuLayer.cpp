#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/Loader.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
	static void onModify(auto& self) {
        (void)self.setHookPriority("MenuLayer::init", -2);
    }
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		if (this->getChildByID("SwelvyBG")) {
			return true;
		}

        if (Mod::get()->getSettingValue<bool>("gd/MenuLayer")) {
			if (CCNode* mainmenu = this->getChildByIDRecursive("main-menu-bg")) {
				if (Mod::get()->getSettingValue<bool>("other/enable-menu-icons")) {
					mainmenu->getChildByID("background")->setVisible(false);
				} else {
					mainmenu->setVisible(false);
				}
			}
			if (Loader::get()->isModLoaded("zalphalaneous.minecraft") && Mod::get()->getSettingValue<bool>("external-mods")) {
				auto panorama = this->getChildByID("zalphalaneous.minecraft/minecraft-panorama");
				if (panorama) {
					panorama->setVisible(false);
				}
			}
			SwelvyBG* swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};