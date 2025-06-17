#pragma once

#include <Geode/Geode.hpp>
#include <unordered_map>

using namespace geode::prelude;

class Tags {
public:
    // Constructor to initialize the tag-to-string and string-to-tag maps
    Tags() {
        log::debug("Initializing Tags...");

        // Populate the maps directly (no hashing needed)
        m_tagMap = {
            {"gd-CreatorLayer", 0},
            {"gd-EditLevelLayer", 1},
            {"gd-GauntletLayer", 2},
            {"gd-GauntletSelectLayer", 3},
            {"gd-GJGarageLayer", 4},
            {"gd-LeaderboardsLayer", 5},
            {"gd-LevelAreaInnerLayer", 6},
            {"gd-LevelAreaLayer", 7},
            {"gd-LevelBrowserLayer", 8},
            {"gd-LevelInfoLayer", 9},
            {"gd-LevelListLayer", 10},
            {"gd-LevelSearchLayer", 11},
            {"gd-LevelSelectLayer", 12},
            {"gd-LoadingLayer", 13},
            {"gd-MenuLayer", 14},
            {"gd-PlayLayer", 15},
            {"gd-SecretLayer", 16},
            {"gd-SecretLayer2", 17},
            {"gd-SecretLayer3", 18},
            {"gd-SecretLayer4", 19},
            {"gd-SecretRewardsLayer", 20},
            {"gd-UIPOptionsLayer", 21},
            {"gd-UIOptionsLayer", 22},
            {"cvolton.betterinfo-CustomCreatorLayer", 23},
            {"cvolton.betterinfo-DailyViewLayer", 24},
            {"cvolton.betterinfo-LevelSearchViewLayer", 25},
            {"cvolton.betterinfo-RewardGroupLayer", 26},
            {"cvolton.betterinfo-RewardViewLayer", 27},
            {"dankmeme.globed2-GlobedLevelListLayer", 28},
            {"dankmeme.globed2-GlobedMenuLayer", 29},
            {"dankmeme.globed2-GlobedServersLayer", 30},
            {"dankmeme.globed2-GlobedSettingsLayer", 31},
            {"geode.loader-ModsLayer", 32},
            {"geode.texture-loader-PackSelectLayer", 33},
            {"hiimjustin000.integrated_demonlist-IDListLayer", 34},
            {"hiimjustin000.integrated_demonlist-IDPackLayer", 35},
            {"km7dev.gdps-switcher-ServerSwitchLayer", 36},
            {"limegradient.betterachievements-BetterAchievementLayer", 37},
            {"minemaker0430.gddp_integration-DPLayer", 38},
            {"minemaker0430.gddp_integration-DPListLayer", 39},
            {"minemaker0430.gddp_integration-DPSearchLayer", 46},
            {"minemaker0430.gddp_integration-RecommendedLayer", 47},
            {"minemaker0430.gddp_integration-RouletteSafeLayer", 48},
            {"omgrod.garage_plus-GPFeedbackLayer", 40},
            {"omgrod.garage_plus-GPKofiLayer", 41},
            {"omgrod.gdstream-StreamLayer", 42},
            {"omgrod.gdstream-StreamCreatorLayer", 43},
            {"thesillydoggo.newgrounds_explorer-NewgroundsBrowserLayer", 44},
            {"uproxide.textures-TextureWorkshopLayer", 45},
            {"omgrod.geodify-GYSettingSelectLayer", 49},
            {"teamtcm.geometry-dash-odyssey-OdysseyComicLayer", 50},
            {"teamtcm.geometry-dash-odyssey-OdysseySelectLayer", 51},
            {"gd-GJShopLayer-Normal", 52},
            {"gd-GJShopLayer-Secret", 53},
            {"gd-GJShopLayer-Community", 54},
            {"gd-GJShopLayer-Mechanic", 55},
            {"gd-GJShopLayer-Diamond", 56},
            {"gdutilsdevs.gdutils-MoreLeaderboards", 57},
            {"teamtcm.geometry-dash-odyssey-GJShopLayer-Carp", 58},
            {"cvolton.betterinfo-LeaderboardViewLayer", 59},
            {"lblazen.gdps_hub-GDPSHubLayer", 60},
            {"gdcpteam.challenge-list-GDCPListLayer", 61},
            {"alphalaneous.random_tab-RandomLayer", 62},
            {"omgrod.geometry-dash-surge-GDSIslandSelectLayer", 63},
            {"omgrod.geometry-dash-surge-GDSBasementLayer", 64},
            {"omgrod.geometry-dash-surge-GDSCreditsLayer", 65},
        };

        log::debug("Tag map populated with {} entries.", m_tagMap.size());

        // Populate the string-to-tag map
        m_stringMap = {
            {0, "gd-CreatorLayer"},
            {1, "gd-EditLevelLayer"},
            {2, "gd-GauntletLayer"},
            {3, "gd-GauntletSelectLayer"},
            {4, "gd-GJGarageLayer"},
            {5, "gd-LeaderboardsLayer"},
            {6, "gd-LevelAreaInnerLayer"},
            {7, "gd-LevelAreaLayer"},
            {8, "gd-LevelBrowserLayer"},
            {9, "gd-LevelInfoLayer"},
            {10, "gd-LevelListLayer"},
            {11, "gd-LevelSearchLayer"},
            {12, "gd-LevelSelectLayer"},
            {13, "gd-LoadingLayer"},
            {14, "gd-MenuLayer"},
            {15, "gd-PlayLayer"},
            {16, "gd-SecretLayer"},
            {17, "gd-SecretLayer2"},
            {18, "gd-SecretLayer3"},
            {19, "gd-SecretLayer4"},
            {20, "gd-SecretRewardsLayer"},
            {21, "gd-UIPOptionsLayer"},
            {22, "gd-UIOptionsLayer"},
            {23, "cvolton.betterinfo-CustomCreatorLayer"},
            {24, "cvolton.betterinfo-DailyViewLayer"},
            {25, "cvolton.betterinfo-LevelSearchViewLayer"},
            {26, "cvolton.betterinfo-RewardGroupLayer"},
            {27, "cvolton.betterinfo-RewardViewLayer"},
            {28, "dankmeme.globed2-GlobedLevelListLayer"},
            {29, "dankmeme.globed2-GlobedMenuLayer"},
            {30, "dankmeme.globed2-GlobedServersLayer"},
            {31, "dankmeme.globed2-GlobedSettingsLayer"},
            {32, "geode.loader-ModsLayer"},
            {33, "geode.texture-loader-PackSelectLayer"},
            {34, "hiimjustin000.integrated_demonlist-IDListLayer"},
            {35, "hiimjustin000.integrated_demonlist-IDPackLayer"},
            {36, "km7dev.gdps-switcher-ServerSwitchLayer"},
            {37, "limegradient.betterachievements-BetterAchievementLayer"},
            {38, "minemaker0430.gddp_integration-DPLayer"},
            {39, "minemaker0430.gddp_integration-DPListLayer"},
            {40, "omgrod.garage_plus-GPFeedbackLayer"},
            {41, "omgrod.garage_plus-GPKofiLayer"},
            {42, "omgrod.gdstream-StreamLayer"},
            {43, "omgrod.gdstream-StreamCreatorLayer"},
            {44, "thesillydoggo.newgrounds_explorer-NewgroundsBrowserLayer"},
            {45, "uproxide.textures-TextureWorkshopLayer"},
            {46, "minemaker0430.gddp_integration-DPSearchLayer"},
            {47, "minemaker0430.gddp_integration-RecommendedLayer"},
            {48, "minemaker0430.gddp_integration-RouletteSafeLayer"},
            {49, "omgrod.geodify-GYSettingSelectLayer"},
            {50, "teamtcm.geometry-dash-odyssey-OdysseyComicLayer"},
            {51, "teamtcm.geometry-dash-odyssey-OdysseySelectLayer"},
            {52, "gd-GJShopLayer-Normal"},
            {53, "gd-GJShopLayer-Secret"},
            {54, "gd-GJShopLayer-Community"},
            {55, "gd-GJShopLayer-Mechanic"},
            {56, "gd-GJShopLayer-Diamond"},
            {57, "gdutilsdevs.gdutils-MoreLeaderboards"},
            {58, "teamtcm.geometry-dash-odyssey-GJShopLayer-Carp"},
            {59, "cvolton.betterinfo-LeaderboardViewLayer"},
            {60, "lblazen.gdps_hub-GDPSHubLayer"},
            {61, "gdcpteam.challenge-list-GDCPListLayer"},
            {62, "alphalaneous.random_tab-RandomLayer"},
            {63, "omgrod.geometry-dash-surge-GDSIslandSelectLayer"},
            {64, "omgrod.geometry-dash-surge-GDSBasementLayer"},
            {65, "omgrod.geometry-dash-surge-GDSCreditsLayer"},
        };

        log::debug("String map populated with {} entries.", m_stringMap.size());
    }

    // Convert a string to a corresponding tag (integer)
    int getTagFromString(std::string name) {
        auto it = m_tagMap.find(name);
        if (it != m_tagMap.end()) {
            log::debug("Found tag: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", name);
        return -1;
    }

    // Convert an integer tag back to the corresponding string
    std::string getStringFromTag(int tag) {
        auto it = m_stringMap.find(tag);
        if (it != m_stringMap.end()) {
            log::debug("Found string: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", tag);
        return "Unknown";
    }

private:
    std::unordered_map<std::string, int> m_tagMap;    // Direct map for string -> tag
    std::unordered_map<int, std::string> m_stringMap;  // Direct map for tag -> string
};
