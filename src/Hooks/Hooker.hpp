
#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayer.hpp>
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
