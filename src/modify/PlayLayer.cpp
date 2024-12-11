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

            SwelvyBG* swelvyBG = SwelvyBG::create(1.5,3);
            swelvyBG->setZOrder(-5);
            swelvyBG->setID("swelvy-background");
            swelvyBG->setScale(2);
            this->getChildByID("main-node")->addChild(swelvyBG);
            swelvyBG->setPosition(-204,-81);
        }

		return true;
	}
};