#include "../../SwelvyBG.hpp"
#include "Geode/cocos/textures/CCTextureCache.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-LoadingLayer");
class $modify(MyLoadingLayer, LoadingLayer) {
	bool init(bool p0) {
		if (!LoadingLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("gd/LoadingLayer")) {
			auto sapphireTexture = CCTextureCache::get()->addImage("sapphire-bg.png"_spr, false);

			if (auto bg = this->getChildByID("bg-texture")) {
				bg->setVisible(false);
			}

			if (Mod::get()->getSettingValue<std::string>("background-type") == "Sapphire") {
				auto sapphireBg = CCSprite::createWithTexture(sapphireTexture);
				sapphireBg->setZOrder(-3);
				sapphireBg->setScaleX(this->getContentSize().width / sapphireBg->getContentSize().width);
				sapphireBg->setScaleY(this->getContentSize().height / sapphireBg->getContentSize().height);
				sapphireBg->setPosition(this->getContentSize() / 2);
				this->addChild(sapphireBg);
			} else {
				SwelvyBG* swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-3);
				this->addChild(swelvyBG);
			}
		}

		return true;
	}
};