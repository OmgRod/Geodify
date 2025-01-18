#include "Geode/binding/FMODAudioEngine.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>

using namespace geode::prelude;

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
public:
    void playMusic(std::string name, bool shouldLoop, float fadeInTime, int channel) {
        log::debug("Playing music: {}", name);
        std::string newName = "ninxout.wav"_spr;
        if ((name.find("menuLoop.mp3") != std::string::npos) && Mod::get()->getSettingValue<bool>("menu-loop")) {
            name = newName;
            log::debug("Changed music to: {}", name);
        }
        FMODAudioEngine::playMusic(name, shouldLoop, fadeInTime, channel);
    }
};