#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 
class DailyViewLayer : public Betterhook::HookBetter { 
    void init(CCNode* _This) override {
         if (auto bg = _This->getChildByID("cvolton.betterinfo/background")) {
            bg->setVisible(false);
        }
        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        _This->addChild(swelvyBG);
    }

    const char* PutLayer() const override { return "DailyViewLayer"; }
};


REGISTER_HookBetter(DailyViewLayer);

