#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer2.hpp>

using namespace geode::prelude;

class $modify(MySecretLayer2, SecretLayer2) {
	bool init() {
		if (!SecretLayer2::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-vault-of-secrets")){
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
