#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelSelectLayer, LevelSelectLayer) {
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/LevelSelectLayer")){
		if (auto bg = this->getChildByID("background")) {
			bg->setVisible(false);
		}
		if (auto ground = this->getChildByID("ground-layer")) {
			ground->setVisible(false);
		}

		auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-3);
		

    	this->addChild(swelvyBG);
		}
		return true;
	}
};