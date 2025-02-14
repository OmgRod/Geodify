#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/UIOptionsLayer.hpp>

using namespace geode::prelude;

class $modify(MyUIOptionsLayer, UIOptionsLayer) {
	bool init(bool p0) {
		if (!UIOptionsLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/UIOptionsLayer")) {
			int lowestZ = INT_MAX;
			CCObject* obj = nullptr;
            auto layer = this->getChildByType<CCLayer*>(0);
			CCARRAY_FOREACH(layer->getChildren(), obj) {
				if (auto node = typeinfo_cast<CCNode*>(obj)) {
					lowestZ = std::min(lowestZ, node->getZOrder());
				}
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(lowestZ - 1);
			layer->addChild(swelvyBG);
		}
		return true;
	}
};