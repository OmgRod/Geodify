#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 
class GPFeedbackLayer : public Betterhook::HookBetter { 
    void init(CCNode* _This) override {
         if (auto bg = _This->getChildByID("menu")->getChildByID("background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-99999);
        swelvyBG->setID("swelvy-background");
        _This->addChild(swelvyBG);
    }

    const char* PutLayer() const override { return "GPFeedbackLayer"; }
};


REGISTER_HookBetter(GPFeedbackLayer);

