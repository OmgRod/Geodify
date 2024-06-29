#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>

using namespace geode::prelude;

class $modify(MySecretRewardsLayer, SecretRewardsLayer) {
	bool init(bool p0) {
		if (!SecretRewardsLayer::init(p0)) {
			return false;
		}

		this->getChildByID("background")->setVisible(false);
        this->getChildByID("top-left-art")->setVisible(false);
        this->getChildByID("top-right-art")->setVisible(false);
        this->getChildByID("floor")->setVisible(false);

		auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-2);
		swelvyBG->setID("swelvy-background");

    	this->addChild(swelvyBG);

		return true;
	}
};