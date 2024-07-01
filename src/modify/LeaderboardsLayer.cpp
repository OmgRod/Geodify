#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;

class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	bool init(LeaderboardState p0) {
		if (!LeaderboardsLayer::init(p0)) {
			return false;
		}

		if (auto value = Mod::get()->getSettingValue<bool>("menus")) {
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}

		return true;
	}
};