
#include "Hooker.hpp"

#include <Geode/Geode.hpp>

namespace Betterhook {
    
    static std::vector<Betterhook::Hook*> ListHooks;
  
    const std::vector<Betterhook::Hook*>& Hook::Hooks() {
        return ListHooks;
    }
     void Hook::registerHook(Betterhook::Hook* hook) {
        ListHooks.push_back(hook);
    }

}
