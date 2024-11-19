#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;

class $modify(MyGauntletLayer, GauntletLayer) {
	bool init(GauntletType p) {
		if (!GauntletLayer::init(p)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-gauntlet-map")){
			auto bg = typeinfo_cast<CCNode*>(this->getChildren()->objectAtIndex(0));
			bg->setVisible(false);
			
			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};