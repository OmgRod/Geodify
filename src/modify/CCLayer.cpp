// #include "../SwelvyBG.hpp"
// #include <Geode/Geode.hpp>
// #include <Geode/modify/CCLayer.hpp>

// using namespace geode::prelude;

// class $modify(MyCCLayer, CCLayer) {
// 	void onEnter() {
// 		CCLayer::onEnter();
// 		if (auto parent = typeinfo_cast<UIOptionsLayer*>(this->getParent())) {
// 			if (Mod::get()->getSettingValue<bool>("gd/UIOptionsLayer")) {
// 				int lowestZ = INT_MAX;
// 				CCObject* obj = nullptr;
// 				CCARRAY_FOREACH(this->getChildren(), obj) {
// 					if (auto node = typeinfo_cast<CCNode*>(obj)) {
// 						lowestZ = std::min(lowestZ, node->getZOrder());
// 					}
// 				}

// 				auto swelvyBG = SwelvyBG::create();
// 				swelvyBG->setZOrder(lowestZ - 1);
// 				this->addChild(swelvyBG);
// 			}
// 		}
// 		if (auto parent = typeinfo_cast<UIPOptionsLayer*>(this->getParent())) {
// 			if (Mod::get()->getSettingValue<bool>("gd/UIPOptionsLayer")) {
// 				int lowestZ = INT_MAX;
// 				CCObject* obj = nullptr;
// 				CCARRAY_FOREACH(this->getChildren(), obj) {
// 					if (auto node = typeinfo_cast<CCNode*>(obj)) {
// 						lowestZ = std::min(lowestZ, node->getZOrder());
// 					}
// 				}

// 				auto swelvyBG = SwelvyBG::create();
// 				swelvyBG->setZOrder(lowestZ - 1);
// 				this->addChild(swelvyBG);
// 			}
// 		}
// 	}
// };