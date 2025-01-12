#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer4.hpp>

using namespace geode::prelude;

class $modify(MySecretLayer4, SecretLayer4) {
	bool init() {
		if (!SecretLayer4::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-chamber-of-time")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-3);
				
	
				this->addChild(swelvyBG);				
			}
		}
		return true;
	}
};
