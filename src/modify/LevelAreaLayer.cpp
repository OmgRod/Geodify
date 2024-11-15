#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelAreaLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelAreaLayer, LevelAreaLayer) {
	bool init() {
		if (!LevelAreaLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-outer-tower")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-2);
				swelvyBG->setID("swelvy-background");
	
				this->addChild(swelvyBG);				
			}
		}
		return true;
	}
};