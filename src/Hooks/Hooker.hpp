
#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>
#include <Geode/modify/CCDirector.hpp>
using namespace geode::prelude;

#define Viper_Hookclass(className)                           \
class className : public CCLayer {                           \
public:                                                      \
    void ____________________DONOTUSE__________________________ViperHookInit();                                       \
};                                                           \
class $modify(CCLayer) {                                     \
    bool init() {                                   \
        if (!CCLayer::init()) return false;                  \
         if (!Mod::get()->getSettingValue<bool>("external-mods")) { \
            return true; \
        } \
		if (auto x = typeinfo_cast<className*>(this)) {      \
        	queueInMainThread([=] {x->____________________DONOTUSE__________________________ViperHookInit();});     return true;          		 	 \
        }                                                    \
        return true;                                         \
    }                                                        \
};                                                           \
void className::____________________DONOTUSE__________________________ViperHookInit()
// PLEASE DON'T USE THIS UNLESS FORCED APON
#define Viper_Hookclass_Scene(unique,className)                           \
class unique##Sillyclass {                                                      \
public:                                                                 \
    void ____________________DONOTUSE__________________________ViperHookInit(CCNode* _This);                                               \
};                                                          \
class $modify(CCDirector) { \
    static void onModify(auto& self) { \
        (void)self.setHookPriority("CCDirector::willSwitchToScene", -999); \
    } \
    void willSwitchToScene(CCScene* scene) { \
        CCDirector::willSwitchToScene(scene); \
        if (!Mod::get()->getSettingValue<bool>("external-mods")) { \
            return; \
        }; \
        if (CCLayer* child = scene->getChildByType<CCLayer>(0)) { \
            if (child->getID() == className) { \
                unique##Sillyclass sillyInstance;       \
                sillyInstance.____________________DONOTUSE__________________________ViperHookInit(child); \
            }; \
        } \
    }                                                 \
};                                                           \
void unique##Sillyclass::____________________DONOTUSE__________________________ViperHookInit(CCNode* _This) 
