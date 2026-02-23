#include <Geode/Geode.hpp>
#include <Geode/loader/Loader.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>

using namespace geode::prelude;
ADD_TAG("geode.loader-ModsLayer");
class $nodeModify(ModsLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<bool>("geode.loader/ModsLayer")) {
            if (!(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme"))) {
                if (auto bg = getChildByID("bg")) {
                    bg->setVisible(false);
                }

                SwelvyBG* swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-1);
                
                addChild(swelvyBG);
            }
        }
    }
};
