#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "../modify/Globed/GlobedServersLayer.hpp"
using namespace geode::prelude;

class $modify(CCDirector) {
    static void onModify(auto& self) {
        (void)self.setHookPriority("CCDirector::willSwitchToScene", -999); 
    }

    void willSwitchToScene(CCScene* scene) {
        CCDirector::willSwitchToScene(scene);
        if (CCLayer* child = getChildOfType<CCLayer>(scene, 0)) {
            const char* className = typeid(*child).name();
            std::string fc = className;
            size_t pos = fc.find("class ");
            if (pos != std::string::npos) {
                std::string tcn = fc.substr(pos + 6);
                log::debug("{}", tcn);
                if (tcn == "GlobedServersLayer") {
                    GlobedServersLayerInit(child);
                }
            }
        }
    }
};

