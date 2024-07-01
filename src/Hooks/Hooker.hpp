#pragma once
#include "Hooker.cpp"
#include <Geode/Geode.hpp>
#define REGISTER_Hook(HookClass) $execute { Betterhook::Hook::registerHook<Hook>(); }
using namespace geode::prelude;
namespace Betterhook {
 class Hook {
    public:
     static void registerHook(Hook* hook);
     static const std::vector<Hook*>& Hooks();
     virtual void init(CCNode* Layer) = 0;
     virtual const char* PutLayer() const = 0;
 };
}