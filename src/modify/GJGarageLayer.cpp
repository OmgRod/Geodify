#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(MyGJGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) {
			return false;
		}

		if (auto bg = this->getChildByID("background")) {
			bg->setVisible(false);
		}

		auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-2);
		swelvyBG->setID("swelvy-background");

    	this->addChild(swelvyBG);

		return true;
	}
};