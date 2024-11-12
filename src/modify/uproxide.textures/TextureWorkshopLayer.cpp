#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 
class TextureWorkshopLayer : public Betterhook::HookBetter { 
    void init(CCNode* _This) override {
        if (CCSprite* bg = _This->getChildByType<CCSprite>(0)) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-2);
        swelvyBG->setID("swelvy-background");
        _This->addChild(swelvyBG);
    }

    const char* PutLayer() const override { return "TextureWorkshopLayer"; }
};


REGISTER_HookBetter(TextureWorkshopLayer);

