#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;

class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	bool init(LeaderboardState p0) {
		if (!LeaderboardsLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/LeaderboardsLayer")) {
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			

			this->addChild(swelvyBG);
		}

		return true;
	}
};