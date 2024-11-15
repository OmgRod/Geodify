#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer.hpp>

using namespace geode::prelude;

class $modify(MySecretLayer, SecretLayer) {
	bool init() {
		if (!SecretLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-vault")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-3);
				swelvyBG->setID("swelvy-background");
	
				this->addChild(swelvyBG);				
			}
		}
		return true;
	}
};
