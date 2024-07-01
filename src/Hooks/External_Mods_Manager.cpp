#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "Hooker.hpp"

using namespace geode::prelude;


void runhooks(CCNode* Send,const std::string& layer) {
        for (Betterhook::HookBetter* hook : Betterhook::HookBetter::Hooks()) {
            if (hook->PutLayer() == layer) {
                hook->init(Send);
            }
        }
    }

class $modify(CCDirector) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("CCDirector::willSwitchToScene", -999); 
    }

    void willSwitchToScene(CCScene* scene) {
        CCDirector::willSwitchToScene(scene);
        if (!Mod::get()->getSettingValue<bool>("external-mods")) {
            return;
        }
        if (CCLayer* child = getChildOfType<CCLayer>(scene, 0)) {
            const char* className = typeid(*child).name();
            std::string fc = className;
            size_t pos = fc.find("class ");
            if (pos != std::string::npos) {
                std::string tcn = fc.substr(pos + 6);
                log::debug("{}", tcn);
                runhooks(child,tcn);
            }
        }
    }
};

