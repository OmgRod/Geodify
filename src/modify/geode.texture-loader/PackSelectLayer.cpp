#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp"

class PackSelectLayer : public Betterhook::HookBetter {
public:
    void init(CCNode* _This) override {
        if (auto bg = _This->getChildByID("background")) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        _This->addChild(swelvyBG);
    }

    void onApply(CCObject* sender) {
        if (auto _This = dynamic_cast<CCNode*>(sender)) {
            if (auto bg = _This->getChildByID("background")) {
                bg->setVisible(false);
            }
            
            SwelvyBG* swelvyBG = SwelvyBG::create();
            swelvyBG->setZOrder(-1);
            swelvyBG->setID("swelvy-background");
            _This->addChild(swelvyBG);
        } else {
            log::debug("Failed to apply SwelvyBG: sender is not a CCNode.");
        }
    }

    const char* PutLayer() const override {
        return "PackSelectLayer";
    }
};

REGISTER_HookBetter(PackSelectLayer);
