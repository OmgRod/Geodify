#include "../../SwelvyBG.hpp"
#include "Geode/cocos/textures/CCTextureCache.h"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-LoadingLayer");
class $modify(MyLoadingLayer, LoadingLayer) {
	struct Fields {
		SwelvyBG* swelvyBG = nullptr;
		CCSprite* sapphireBg = nullptr;
	};

	bool init(bool p0) {
		if (!LoadingLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("gd/LoadingLayer")) {
			m_fields->swelvyBG = SwelvyBG::create();
			m_fields->swelvyBG->setZOrder(-3);
			this->addChild(m_fields->swelvyBG);

			if (Mod::get()->getSettingValue<std::string>("background-type") == "Sapphire") {
				CCTextureCache::get()->addImageAsync(
					"sapphire-bg.png"_spr,
					this,
					menu_selector(MyLoadingLayer::loadSapphireBGAsync),
					CCTexture2DPixelFormat::kCCTexture2DPixelFormat_Default
				);
			}
		}

		return true;
	}

	void loadSapphireBGAsync(CCObject* sender) {
		CCTexture2D* sapphireTexture = static_cast<CCTexture2D*>(sender);
		if (sapphireTexture) {
			this->removeChild(m_fields->swelvyBG);
			m_fields->sapphireBg = CCSprite::createWithTexture(sapphireTexture);
			m_fields->sapphireBg->setZOrder(-3);
			m_fields->sapphireBg->setScaleX(this->getContentSize().width / m_fields->sapphireBg->getContentSize().width);
			m_fields->sapphireBg->setScaleY(this->getContentSize().height / m_fields->sapphireBg->getContentSize().height);
			m_fields->sapphireBg->setPosition(this->getContentSize() / 2);
			this->addChild(m_fields->sapphireBg);
		} else {
			log::error("Failed to load Sapphire background texture: sapphire-bg.png");
		}
	}
};