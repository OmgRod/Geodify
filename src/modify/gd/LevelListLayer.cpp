#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelListLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelListLayer, LevelListLayer) {
	bool init(GJLevelList* list) {
		if (!LevelListLayer::init(list)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/LevelListLayer")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-2);
				
				
				this->addChild(swelvyBG);							
			}
		}
		return true;
	}
};