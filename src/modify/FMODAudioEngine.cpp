#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>
/// todo check on android32, ios and mac (@Cosmella-v)
#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
using namespace geode::prelude;
struct FMODEngineSaved {
    gd::string name; bool shouldLoop; float fadeInTime; int channel;
}; FMODEngineSaved Saved;

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
public:
    void playMusic(gd::string name, bool shouldLoop, float fadeInTime, int channel) {
        log::debug("Playing music: {}", name);
        std::string nameStr = name; 
        Saved.name = name;
        Saved.shouldLoop = shouldLoop;
        Saved.fadeInTime = fadeInTime;
        Saved.channel = channel;
        if (nameStr.find("menuLoop.mp3") != std::string::npos &&
            Mod::get()->getSettingValue<bool>("menu-loop")) 
        {
            log::debug("Changed music to: ninxout.wav");
            return FMODAudioEngine::playMusic("ninxout.wav"_spr, shouldLoop, fadeInTime, channel);
        }

        FMODAudioEngine::playMusic(name, shouldLoop, fadeInTime, channel);
    }
};

$on_mod(Loaded) {
	listenForSettingChanges<bool>("menu-loop", [](bool enabled) {
        if (Saved.name == "menuLoop.mp3") {
		    FMODAudioEngine::sharedEngine()->playMusic("menuLoop.mp3", Saved.shouldLoop, Saved.fadeInTime, Saved.channel);
        };
	});
};
