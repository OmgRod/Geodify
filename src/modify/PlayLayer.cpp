#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPlayLayer, PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
			return false;
		}

        auto bgOn = Mod::get()->getSettingValue<bool>("level-bg");

        if (bgOn) {
            if (auto bg = this->getChildByID("main-node")->getChildByID("background")) {
                bg->setVisible(false);
            }

            auto swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-2);
            swelvyBG->setID("swelvy-background");

            this->getChildByID("main-node")->addChild(swelvyBG);
        }

		return true;
	}
};