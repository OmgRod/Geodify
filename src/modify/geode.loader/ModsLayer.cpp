#include <Geode/Geode.hpp>
#include <Geode/loader/Loader.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp"

using namespace geode::prelude;

class ModsLayer : public Betterhook::HookBetter { 
    void init(CCNode* _This) override {
        if (!(Loader::get()->getSettingValue<bool>("enable-geode-theme"))) {
            if (auto bg = _This->getChildByID("bg")) {
                bg->setVisible(false);
            }

            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-1);
            swelvyBG->setID("swelvy-background");
            _This->addChild(swelvyBG);
        }
    }

    const char* PutLayer() const override { return "ModsLayer"; }
};


REGISTER_HookBetter(ModsLayer);

