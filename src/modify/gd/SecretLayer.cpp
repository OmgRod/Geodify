#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer.hpp>

using namespace geode::prelude;

class $modify(MySecretLayer, SecretLayer) {
	bool init() {
		if (!SecretLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/SecretLayer")){
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
