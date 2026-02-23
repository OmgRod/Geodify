#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>

using namespace geode::prelude;
ADD_TAG("omgrod.garage_plus-StreamCreatorLayer");
class $nodeModify(StreamCreatorLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<bool>("omgrod.gdstream/StreamCreatorLayer")) {
            if (auto bg = this->getChildByID("menu")->getChildByID("background")) {
                bg->setVisible(false);
            }

            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-99999);
            
            this->addChild(swelvyBG);
        }
    }
};