#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <Geode/modify/GJShopLayer.hpp>

using namespace geode::prelude;

class $modify(MyGJShopLayer, GJShopLayer) {
	bool init(ShopType p0) {
		if (!GJShopLayer::init(p0)) {
			return false;
		}
        if (p0 == ShopType::Normal) {
            if (Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Normal")){
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                

                this->addChild(swelvyBG);
            }
        } else if (p0 == ShopType::Secret) {
            if (Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Secret")){
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                

                this->addChild(swelvyBG);
            }
        } else if (p0 == ShopType::Community) {
            if (Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Community")){
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                

                this->addChild(swelvyBG);
            }
        } else if (p0 == ShopType::Mechanic) {
            if (Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Mechanic")){
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                

                this->addChild(swelvyBG);
            }
        } else if (p0 == ShopType::Diamond) {
            if (Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Diamond")){
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                

                this->addChild(swelvyBG);
            }
        }
		return true;
	}
};