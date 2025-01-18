#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/NodeModding.h>

using namespace geode::prelude;

class $nodeModify(StreamLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<bool>("omgrod.gdstream/StreamLayer")) {
            if (auto bg = this->getChildByID("menu")->getChildByID("background")) {
                bg->setVisible(false);
            }

            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-99999);
            
            this->addChild(swelvyBG);
        }
    }
};