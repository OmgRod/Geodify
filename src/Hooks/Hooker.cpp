
#pragma once
#include "Hooker.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace Betterhook {
    
    static std::vector<Betterhook::Hook*> HooksTable;
  
    const std::vector<Betterhook::Hook*>& Hook::Hooks() {
        return HooksTable;
    }
     void Hook::registerHook(Hook* hook) {
        HooksTable.push_back(hook);
    }

}
