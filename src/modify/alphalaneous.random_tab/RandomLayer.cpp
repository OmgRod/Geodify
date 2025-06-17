#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/NodeModding.h>

using namespace geode::prelude;

class $nodeModify(MyRandomLayer, RandomLayer) {\
    void modify() {
        if (Mod::get()->getSettingValue<bool>("alphalaneous.random_tab/RandomLayer")) {
            if (auto bg = getChildByType<CCSprite>(-1)) {
                bg->setVisible(false);
                SwelvyBG* swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                addChild(swelvyBG);

                for (int i = 0; i < 4; ++i) {
                    if (auto newBg = getChildByType<CCScale9Sprite>(i)) {
                        newBg->setColor(ccColor3B{0, 0, 0});
                        newBg->setOpacity(60);
                    } else {
                        log::debug("Background not found or wrong type at index {}", i);
                    }
                }
            }
        }
    }
};