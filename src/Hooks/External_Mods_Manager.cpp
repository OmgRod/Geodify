#include <Geode/Geode.hpp>
#include <Geode/modify/CCDirector.hpp>
#include "Hooker.hpp"
#if defined(GEODE_IS_ANDROID)
#include <cxxabi.h>
#endif
#include <typeinfo>
#include <memory>
#include <string>
#include <unordered_map>

using namespace geode::prelude;


void runhooks(CCNode* Send,const std::string& layer) {
        for (Betterhook::HookBetter* hook : Betterhook::HookBetter::Hooks()) {
            if (hook->PutLayer() == layer) {
                hook->init(Send);
            }
        }
    }

#if defined(GEODE_IS_ANDROID)
    std::string demangle(const char* mangledName) {
        static std::unordered_map<std::string, std::string> cache;
        

        auto it = cache.find(mangledName);
        if (it != cache.end()) {
            return it->second;
        }

        int status = 0;
        char* demangled = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
        std::string result;
        
        if (status == 0) {
            result = demangled;
        } else {
            result = mangledName;
        }

        free(demangled);


        cache[mangledName] = result;
        return result;
    }
#endif

std::string getclass(auto object) {
const char* className = typeid(*object).name();
#if defined(GEODE_IS_ANDROID)
    return demangle(className);
#else
     size_t pos = fc.find("class ");
            if (pos != std::string::npos) {
                return fc.substr(pos + 6);
            } else {
                return fc;
            }
#endif


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
            std::string fc = getclass(child);
            size_t pos = fc.find("class ");
            if (pos != std::string::npos) {
                std::string tcn = fc.substr(pos + 6);
                #ifndef GITHUB_ACTIONS
                    log::debug("{}", tcn);
                #endif
                runhooks(child,tcn);
            }
        }
    }
};

