
#include "Hooker.hpp"

#include <Geode/Geode.hpp>

namespace Betterhook {
    
    static std::vector<HookBetter*> ListHooks;
  
    const std::vector<HookBetter*>& HookBetter::Hooks() {
        return ListHooks;
    }
    
     void HookBetter::registerHook(HookBetter* hook) {
        ListHooks.push_back(hook);
    }

}
