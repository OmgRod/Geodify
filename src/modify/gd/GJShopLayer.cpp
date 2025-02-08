#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <Geode/modify/GJShopLayer.hpp>
#include <alphalaneous.alphas_geode_utils/include/NodeModding.h>

using namespace geode::prelude;

class $modify(MyGJShopLayer, GJShopLayer) {
    bool init(ShopType p0) {
        if (!GJShopLayer::init(p0)) {
            return false;
        }

        bool shouldReplaceBG = false;
        switch (p0) {
            case ShopType::Normal:
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Normal");
                break;
            case ShopType::Secret:
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Secret");
                break;
            case ShopType::Community:
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Community");
                break;
            case ShopType::Mechanic:
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Mechanic");
                break;
            case ShopType::Diamond:
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Diamond");
                break;
            default:
                break;
        }

        if (static_cast<int>(p0) == 6) {
            shouldReplaceBG = Mod::get()->getSettingValue<bool>("teamtcm.geometry-dash-odyssey/GJShopLayer-Carp");
        }

        if (shouldReplaceBG) {
            if (auto bg = this->getChildByID("background")) {
                bg->setVisible(false);
            }
            this->getChildByType<CCSprite>(0)->setVisible(false);
            auto swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-999);
            this->addChild(swelvyBG);
        }
        
        return true;
    }
};