#pragma once

#include <Geode/Geode.hpp>
#include <unordered_map>
#include <string_view>

using namespace geode::prelude;
class Tags {
public:
    inline static int gm_id = 0;
    static inline std::unordered_map<std::string, int> gm_tagMap;
    static inline std::unordered_map<int, std::string> gm_stringMap;
    static const inline std::vector<std::tuple<std::string, std::string, std::string>> modData = {
        { "Geometry Dash", "RobTop", "gd" },
        { "Geode", "Geode Team", "geode.loader" },
        { "BetterInfo", "Cvolton", "cvolton.betterinfo" },
        { "Globed", "dankmeme", "dankmeme.globed2" },
        { "Texture Loader", "Geode Team", "geode.texture-loader" },
        { "Integrated Demonlist", "hiimjustin000", "hiimjustin000.integrated_demonlist" },
        { "GDPS Switcher", "km7dev", "km7dev.gdps-switcher" },
        { "BetterAchievements", "limegradient", "limegradient.betterachievements" },
        { "GDDP Integration", "Minemaker0430", "minemaker0430.gddp_integration" },
        { "Garage Plus", "OmgRod", "omgrod.garage_plus" },
        { "GDStream", "OmgRod", "omgrod.gdstream" },
        { "Geodify", "OmgRod & Cosmella-v", "omgrod.geodify" },
        { "Newgrounds Explorer", "TheSillyDoggo", "thesillydoggo.newgrounds_explorer" },
        { "Texture Workshop", "Uproxide", "uproxide.textures" },
        { "Geometry Dash: Odyssey", "chumiu", "teamtcm.geometry-dash-odyssey" },
        { "GDUtils", "Jouca & Firee", "gdutilsdevs.gdutils" },
        { "GDPS Hub", "GDPS Hub Team + 2 more", "lblazen.gdps_hub" },
        { "GDCP List Integration", "GDCP Team + 2 more", "gdcpteam.challenge-list" },
        { "Random Tab", "Alphalaneous", "alphalaneous.random_tab" },
        { "Geometry Dash: Surge", "OmgRod", "omgrod.geometry-dash-surge" },
        { "SecretLayer6", "TimeStepYT", "timestepyt.secretlayer6" },
    };
    static void addTag(std::string name) {
        int value = gm_id;
        gm_id+=1;
        log::debug("{} {}",name, value);
        gm_tagMap.emplace(name, value);
        gm_stringMap.emplace(value, name);
    }

     int getTagFromString(std::string name) {
        auto it = gm_tagMap.find(name);
        if (it != gm_tagMap.end()) {
            log::debug("Found tag: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", name);
        return -1;
    }

    std::string getStringFromTag(int tag) {
        auto it = gm_stringMap.find(tag);
        if (it != gm_stringMap.end()) {
            log::debug("Found string: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", tag);
        return "Unknown";
    }
};

#define __CONCAT_DETAIL(x, y) x##y
#define __CONCAT(x, y) __CONCAT_DETAIL(x, y)

#define ADD_TAG(name) \
    namespace { \
        struct __CONCAT(AutoRegisterTag_, __LINE__) { \
            __CONCAT(AutoRegisterTag_, __LINE__)() { \
                Tags::addTag(name); \
            } \
        } __CONCAT(autoRegisterTag_, __LINE__); \
    } \
    static_assert(true, "")

