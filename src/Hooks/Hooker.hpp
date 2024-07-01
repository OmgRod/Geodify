#pragma once

#include "Hooker.cpp"
#include <Geode/Geode.hpp>

#define REGISTER_Hook(HookClass) $execute { Betterhook::Hook::registerHook<Hook>(); }

using namespace geode::prelude;

namespace Betterhook {
 class HookBetter {
    public:
     static void registerHook(HookBetter* hook);
     static const std::vector<HookBetter*>& Hooks();
     virtual void init(cocos2d::CCNode* Layer) = 0;
     virtual const char* PutLayer() const = 0;
 };
}
