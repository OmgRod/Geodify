#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-LeaderboardsLayer");	
class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	bool init(LeaderboardType type, LeaderboardStat stat) {
		if (!LeaderboardsLayer::init(type, stat)) return false;
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