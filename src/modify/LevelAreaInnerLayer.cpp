#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelAreaInnerLayer, LevelAreaInnerLayer) {
	bool init() {
		if (!LevelAreaInnerLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-inner-tower")){
			auto bg = static_cast<CCNode*>(this->getChildren()->objectAtIndex(0));
			bg->setVisible(false);
			
			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};