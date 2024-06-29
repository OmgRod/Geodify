#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) {
			return false;
		}

		this->getChildByID("background")->setVisible(false);

		CCScale9Sprite* levelSearchBg = static_cast<CCScale9Sprite*>(this->getChildByID("level-search-bg"));
		levelSearchBg->setColor(ccc3(0, 0, 0));
		levelSearchBg->setOpacity(85);

		CCScale9Sprite* levelSearchBarBg = static_cast<CCScale9Sprite*>(this->getChildByID("level-search-bar-bg"));
		levelSearchBarBg->setColor(ccc3(0, 0, 0));
		levelSearchBarBg->setOpacity(85);

		CCScale9Sprite* quickSearchBg = static_cast<CCScale9Sprite*>(this->getChildByID("quick-search-bg"));
		quickSearchBg->setColor(ccc3(0, 0, 0));
		quickSearchBg->setOpacity(85);

		CCScale9Sprite* difficultyFiltersBg = static_cast<CCScale9Sprite*>(this->getChildByID("difficulty-filters-bg"));
		difficultyFiltersBg->setColor(ccc3(0, 0, 0));
		difficultyFiltersBg->setOpacity(85);

		CCScale9Sprite* lengthFiltersBg = static_cast<CCScale9Sprite*>(this->getChildByID("length-filters-bg"));
		lengthFiltersBg->setColor(ccc3(0, 0, 0));
		lengthFiltersBg->setOpacity(85);

		CCNode* searchBar = this->getChildByID("search-bar");
		if (searchBar) {
			CCArray* children = searchBar->getChildren();
			CCObject* obj = nullptr;
			CCARRAY_FOREACH(children, obj) {
				CCLabelBMFont* label = dynamic_cast<CCLabelBMFont*>(obj);
				if (label) {
					label->setColor(ccc3(255, 255, 255));
				}
			}
		}

		auto swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-3);
		swelvyBG->setID("swelvy-background");

    	this->addChild(swelvyBG);

		return true;
	}
};