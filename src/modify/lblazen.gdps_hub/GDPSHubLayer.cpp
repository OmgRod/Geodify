#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>

using namespace geode::prelude;
ADD_TAG("lblazen.gdps_hub-GDPSHubLayer");
class $nodeModify(MyGDPSHubLayer, GDPSHubLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<bool>("lblazen.gdps_hub/GDPSHubLayer")) {
            if (auto bg = this->getChildByID("background")) {
                bg->setVisible(false);
                this->getChildByID("swelvy-node")->setVisible(false);
                SwelvyBG* swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(bg->getZOrder() - 1);
                this->addChild(swelvyBG);
            }
        }
    }
};