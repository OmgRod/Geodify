#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/UIPOptionsLayer.hpp>

using namespace geode::prelude;

class $modify(MyUIPOptionsLayer, UIPOptionsLayer) {
	bool init() {
		if (!UIPOptionsLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-control-settings")){
			this->setOpacity(0);
			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};
