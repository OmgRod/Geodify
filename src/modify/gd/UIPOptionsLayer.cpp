#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/UIPOptionsLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-UIPOptionsLayer");
class $modify(MyUIPOptionsLayer, UIPOptionsLayer) {
	bool init() {
		if (!UIPOptionsLayer::init()) return false;
		if (Mod::get()->getSettingValue<bool>("gd/UIPOptionsLayer")) {
			int lowestZ = INT_MAX;
            auto layer = this->getChildByType<CCLayer*>(0);
			for (auto obj : layer->getChildrenExt<CCNode*>()) {
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
