#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/EditLevelLayer.hpp>

using namespace geode::prelude;

class $modify(MyEditLevelLayer, EditLevelLayer) {
    bool init(GJGameLevel* p0) {
        if (!EditLevelLayer::init(p0)) {
            return false;
        }
        if (Mod::get()->getSettingValue<bool>("show-edit-level")) {
            if (auto bg = this->getChildByID("background")) {
                bg->setVisible(false);
            }

            if (auto levelNameBG = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("level-name-background"))) {
                levelNameBG->setColor(ccColor3B{0, 0, 0});
                levelNameBG->setOpacity(60);
            } else {
                log::debug("level-name-background not found or wrong type");
            }

            if (auto descriptionBG = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("description-background"))) {
                descriptionBG->setColor(ccColor3B{0, 0, 0});
                descriptionBG->setOpacity(60);
            } else {
                log::debug("description-background not found or wrong type");
            }

            auto swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-2);
            

            this->addChild(swelvyBG);
        }
        return true;
    }
};
