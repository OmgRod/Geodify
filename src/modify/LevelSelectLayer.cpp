#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelSelectLayer, LevelSelectLayer) {
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) {
			return false;
		}

		this->getChildByID("background")->setVisible(false);
		this->getChildByID("ground-layer")->setVisible(false);

		auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-3);
		swelvyBG->setID("swelvy-background");

    	this->addChild(swelvyBG);

		return true;
	}
};