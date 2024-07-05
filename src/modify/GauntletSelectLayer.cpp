#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>

using namespace geode::prelude;

class $modify(MyGauntletSelectLayer, GauntletSelectLayer) {
	bool init(int p0) {
		if (!GauntletSelectLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-gauntlet-select")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};