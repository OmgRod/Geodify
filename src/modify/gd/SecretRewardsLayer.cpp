#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>

using namespace geode::prelude;

class $modify(MySecretRewardsLayer, SecretRewardsLayer) {
	bool init(bool p0) {
		if (!SecretRewardsLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/SecretRewardsLayer")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
			}
			if (auto tlArt = this->getChildByID("top-left-art")) {
				tlArt->setVisible(false);
			}
			if (auto trArt = this->getChildByID("top-right-art")) {
				trArt->setVisible(false);
			}
			if (auto floor = this->getChildByID("floor")) {
				floor->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};