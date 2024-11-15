#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>

using namespace geode::prelude;

class $modify(MyEditLevelLayer, EditLevelLayer) {
	bool init(GJGameLevel* p0) {
		if (!EditLevelLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("show-edit-level")){
			if (auto bg = this->getChildByID("background")){
				bg->setVisible(false);
			}

			CCScale9Sprite* levelNameBG = dynamic_cast<CCScale9Sprite*>(this->getChildByID("level-name-background"));
			if (levelNameBG) {
				levelNameBG->setColor(ccColor3B(0, 0, 0));
        		levelNameBG->setOpacity(60);
			} else {
				log::debug("Failed to cast level-name-background to CCSprite");
			}

			CCScale9Sprite* descriptionBG = dynamic_cast<CCScale9Sprite*>(this->getChildByID("description-background"));
			if (descriptionBG) {
				descriptionBG->setColor(ccColor3B(0, 0, 0));
        		descriptionBG->setOpacity(60);
			} else {
				log::debug("Failed to cast description-background to CCSprite");
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			swelvyBG->setID("swelvy-background");

			this->addChild(swelvyBG);
		}
		return true;
	}
};