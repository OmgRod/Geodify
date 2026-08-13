#include <Geode/Geode.hpp>
#include "../SwelvyBG.hpp"
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/GauntletLayer.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/LeaderboardsLayer.hpp>
#include <Geode/modify/LevelAreaInnerLayer.hpp>
#include <Geode/modify/LevelAreaLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/LevelListLayer.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/SecretLayer.hpp>
#include <Geode/modify/SecretLayer2.hpp>
#include <Geode/modify/SecretLayer3.hpp>
#include <Geode/modify/SecretLayer4.hpp>
#include <Geode/modify/SecretLayer5.hpp>
#include <Geode/modify/SecretRewardsLayer.hpp>
#include <Geode/modify/UIOptionsLayer.hpp>
#include <Geode/modify/UIPOptionsLayer.hpp>

using namespace geode::prelude;

// Geometry Dash

ADD_TAG("gd/CreatorLayer");
class $modify(MyCreatorLayer, CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) return false;
		if (Mod::get()->getSettingValue<bool>("gd/CreatorLayer")) {
            if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);

                this->addChild(swelvyBG);
            }
		}
		return true;
	}
};

ADD_TAG("gd/EditLevelLayer");
class $modify(MyEditLevelLayer, EditLevelLayer) {
    bool init(GJGameLevel* p0) {
        if (!EditLevelLayer::init(p0)) {
            return false;
        }
        if (Mod::get()->getSettingValue<bool>("gd/EditLevelLayer")) {
            if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                if (auto levelNameBG = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("level-name-background"))) {
                    levelNameBG->setColor(ccColor3B{0, 0, 0});
                    levelNameBG->setOpacity(60);
                } else {
                    log::debug("level-name-background not found or wrong type");
                }

                if (auto descriptionBG = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("description-background"))) {
                    descriptionBG->setColor(ccColor3B{0, 0, 0});
                    descriptionBG->setOpacity(60);
                } else {
                    log::debug("description-background not found or wrong type");
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);

                this->addChild(swelvyBG);
            }
        }
        return true;
    }
};

ADD_TAG("gd/GauntletLayer");
class $modify(MyGauntletLayer, GauntletLayer) {
	bool init(GauntletType p) {
		if (!GauntletLayer::init(p)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/GauntletLayer")) {
                auto bg = typeinfo_cast<CCNode*>(this->getChildren()->objectAtIndex(0));
                if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") bg->setVisible(false);
                
                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);
                
                this->addChild(swelvyBG);
            }
        }
		return true;
	}
};

ADD_TAG("gd/GauntletSelectLayer");
class $modify(MyGauntletSelectLayer, GauntletSelectLayer) {
	bool init(int p0) {
		if (!GauntletSelectLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/GauntletSelectLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);
                

                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/GJGarageLayer");
class $modify(MyGJGarageLayer, GJGarageLayer) {
	bool init() {
		if (!GJGarageLayer::init()) return false;
		if (Mod::get()->getSettingValue<bool>("gd/GJGarageLayer")) {
            if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);

                this->addChild(swelvyBG);
            }
		}
		return true;
	}
};

ADD_TAG("gd/GJShopLayer-Normal", "Scratch's Shop");
ADD_TAG("gd/GJShopLayer-Secret", "Secret Shop");
ADD_TAG("gd/GJShopLayer-Community", "Community Shop");
ADD_TAG("gd/GJShopLayer-Mechanic", "Mechanic's Shop");
ADD_TAG("gd/GJShopLayer-Diamond", "Diamond Shop");
ADD_TAG("teamtcm.geometry-dash-odyssey/GJShopLayer-Carp", "Carp's Shop");

class $modify(MyGJShopLayer, GJShopLayer) {
    bool init(ShopType p0) {
        if (!GJShopLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            bool shouldReplaceBG = false;
            switch (p0) {
                case ShopType::Normal:
                    shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Normal");
                    break;
                case ShopType::Secret:
                    shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Secret");
                    break;
                case ShopType::Community:
                    shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Community");
                    break;
                case ShopType::Mechanic:
                    shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Mechanic");
                    break;
                case ShopType::Diamond:
                    shouldReplaceBG = Mod::get()->getSettingValue<bool>("gd/GJShopLayer-Diamond");
                    break;
                default:
                    break;
            }

            if (static_cast<int>(p0) == 6) {
                shouldReplaceBG = Mod::get()->getSettingValue<bool>("teamtcm.geometry-dash-odyssey/GJShopLayer-Carp");
            }

            if (shouldReplaceBG) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }
                this->getChildByType<CCSprite>(0)->setVisible(false);
                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                this->addChild(swelvyBG);
            }
        }
        
        return true;
    }
};

ADD_TAG("gd/LeaderboardsLayer");
class $modify(MyLeaderboardsLayer, LeaderboardsLayer) {
	bool init(LeaderboardType type, LeaderboardStat stat) {
		if (!LeaderboardsLayer::init(type, stat)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LeaderboardsLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-3);
                
                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelAreaInnerLayer");
class $modify(MyLevelAreaInnerLayer, LevelAreaInnerLayer) {
	bool init(bool p0) {
		if (!LevelAreaInnerLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelAreaInnerLayer")) {
                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);
                

                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelAreaLayer");
class $modify(MyLevelAreaLayer, LevelAreaLayer) {
	bool init() {
		if (!LevelAreaLayer::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelAreaLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-2);
                    
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelBrowserLayer");
class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {
	bool init(GJSearchObject* p0) {
		if (!LevelBrowserLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelBrowserLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-2);
                    
        
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelInfoLayer");
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelInfoLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);
                
                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelListLayer");
class $modify(MyLevelListLayer, LevelListLayer) {
	bool init(GJLevelList* list) {
		if (!LevelListLayer::init(list)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelListLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-2);
                    
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelSearchLayer");
class $modify(MyLevelSearchLayer, LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelSearchLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }

                CCScale9Sprite* levelSearchBg = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("level-search-bg"));
                levelSearchBg->setColor(ccc3(0, 0, 0));
                levelSearchBg->setOpacity(85);

                CCScale9Sprite* levelSearchBarBg = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("level-search-bar-bg"));
                levelSearchBarBg->setColor(ccc3(0, 0, 0));
                levelSearchBarBg->setOpacity(85);

                CCScale9Sprite* quickSearchBg = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("quick-search-bg"));
                quickSearchBg->setColor(ccc3(0, 0, 0));
                quickSearchBg->setOpacity(85);

                CCScale9Sprite* difficultyFiltersBg = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("difficulty-filters-bg"));
                difficultyFiltersBg->setColor(ccc3(0, 0, 0));
                difficultyFiltersBg->setOpacity(85);

                CCScale9Sprite* lengthFiltersBg = typeinfo_cast<CCScale9Sprite*>(this->getChildByID("length-filters-bg"));
                lengthFiltersBg->setColor(ccc3(0, 0, 0));
                lengthFiltersBg->setOpacity(85);

                CCNode* searchBar = this->getChildByID("search-bar");
                if (searchBar) {
                    CCArray* children = searchBar->getChildren();
                    for (auto obj : CCArrayExt<CCObject*>(children)) {
                        CCLabelBMFont* label = typeinfo_cast<CCLabelBMFont*>(obj);
                        if (label) {
                            label->setColor(ccc3(255, 255, 255));
                        }
                    }
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-3);
                

                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/LevelSelectLayer");
class $modify(MyLevelSelectLayer, LevelSelectLayer) {
	bool init(int page) {
		if (!LevelSelectLayer::init(page)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LevelSelectLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }
                if (auto ground = this->getChildByID("ground-layer")) {
                    ground->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-3);
                

                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/LoadingLayer");
class $modify(MyLoadingLayer, LoadingLayer) {
	bool init(bool p0) {
		if (!LoadingLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/LoadingLayer")) {
                if (auto bg = this->getChildByID("bg-texture")) {
                    bg->setVisible(false);
                }

                auto winSize = CCDirector::sharedDirector()->getWinSize();

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-999);
                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/MenuLayer");
class $modify(MenuLayer) {
	static void onModify(auto& self) {
        (void)self.setHookPriority("MenuLayer::init", -2);
    }

	bool init() {
		if (!MenuLayer::init()) return false;

		if (this->getChildByID("SwelvyBG")) {
			return true;
		}

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/MenuLayer")) {
                if (CCNode* mainmenu = this->getChildByIDRecursive("main-menu-bg")) {
                    if (Mod::get()->getSettingValue<bool>("other/enable-menu-icons")) {
                        mainmenu->getChildByID("background")->setVisible(false);
                    } else {
                        mainmenu->setVisible(false);
                    }
                }
                if (Loader::get()->isModLoaded("zalphalaneous.minecraft") && Mod::get()->getSettingValue<bool>("external-mods")) {
                    auto panorama = this->getChildByID("zalphalaneous.minecraft/minecraft-panorama");
                    if (panorama) {
                        panorama->setVisible(false);
                    }
                }
                SwelvyBG* swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-3);
                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/PlayLayer");
class $modify(MyPlayLayer, PlayLayer) {
	bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
		if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            auto bgOn = Mod::get()->getSettingValue<bool>("gd/PlayLayer");

            if (bgOn) {
                if (auto bg = this->getChildByID("main-node")->getChildByID("background")) {
                    bg->setVisible(false);
                }

                SwelvyBG* swelvyBG = SwelvyBG::create(1.5,3);
                swelvyBG->setZOrder(-5);
                
                swelvyBG->setScale(2);
                this->getChildByID("main-node")->addChild(swelvyBG);
                swelvyBG->setPosition(-204,-81);
            }
        }

		return true;
	}
};

ADD_TAG("gd/SecretLayer");
class $modify(MySecretLayer, SecretLayer) {
	bool init() {
		if (!SecretLayer::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/SecretLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-3);
                    
        
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
	}
};

ADD_TAG("gd/SecretLayer2");
class $modify(MySecretLayer2, SecretLayer2) {
	bool init() {
		if (!SecretLayer2::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/SecretLayer2")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-3);
                    
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
    }
};

ADD_TAG("gd/SecretLayer3");
class $modify(MySecretLayer3, SecretLayer3) {
	bool init() {
		if (!SecretLayer3::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/SecretLayer3")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-3);
                    
                    this->addChild(swelvyBG);
                }
            }
        }
        
		return true;
	}
};

ADD_TAG("gd/SecretLayer4");
class $modify(MySecretLayer4, SecretLayer4) {
	bool init() {
		if (!SecretLayer4::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/SecretLayer4")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    auto swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-3);
                    
        
                    this->addChild(swelvyBG);
                }
            }
        }

		return true;
	}
};

ADD_TAG("gd/SecretLayer5");
SET_SWELVY_SPRITE(SecretLayer5, "gd/SecretLayer5");

ADD_TAG("gd/SecretRewardsLayer");
class $modify(MySecretRewardsLayer, SecretRewardsLayer) {
	bool init(bool p0) {
		if (!SecretRewardsLayer::init(p0)) return false;
        
        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/SecretRewardsLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                }
                if (auto tlArt = this->getChildByID("top-left-art")) {
                    tlArt->setVisible(false);
                }
                if (auto trArt = this->getChildByID("top-right-art")) {
                    trArt->setVisible(false);
                }
                if (auto floor = this->getChildByID("floor")) {
                    floor->setVisible(false);
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(-2);
                

                this->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/UIOptionsLayer");
class $modify(MyUIOptionsLayer, UIOptionsLayer) {
	bool init(bool p0) {
		if (!UIOptionsLayer::init(p0)) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/UIOptionsLayer")) {
                int lowestZ = INT_MAX;
                auto layer = this->getChildByType<CCLayer*>(0);
                for (auto obj : layer->getChildrenExt<CCNode*>()) {
                    if (auto node = typeinfo_cast<CCNode*>(obj)) {
                        lowestZ = std::min(lowestZ, node->getZOrder());
                    }
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(lowestZ - 1);
                layer->addChild(swelvyBG);
            }
        }

		return true;
	}
};

ADD_TAG("gd/UIPOptionsLayer");
class $modify(MyUIPOptionsLayer, UIPOptionsLayer) {
	bool init() {
		if (!UIPOptionsLayer::init()) return false;

        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("gd/UIPOptionsLayer")) {
                int lowestZ = INT_MAX;
                auto layer = this->getChildByType<CCLayer*>(0);
                for (auto obj : layer->getChildrenExt<CCNode*>()) {
                    if (auto node = typeinfo_cast<CCNode*>(obj)) {
                        lowestZ = std::min(lowestZ, node->getZOrder());
                    }
                }

                auto swelvyBG = SwelvyBG::create();
                swelvyBG->setZOrder(lowestZ - 1);
                layer->addChild(swelvyBG);
            }
        }

		return true;
	}
};

// abb2k.gdwt

ADD_TAG("abb2k.gdwt/GDWTLayer");
SET_SWELVY_SPRITE(GDWTLayer, "abb2k.gdwt/GDWTLayer");

// alphalaneous.random_tab

ADD_TAG("alphalaneous.random_tab/RandomLayer");
class $nodeModify(MyRandomLayer, RandomLayer) {\
    void modify() {
        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("alphalaneous.random_tab/RandomLayer")) {
                if (auto bg = this->template getChildByType<CCSprite>(-1)) {
                    bg->setVisible(false);
                    SwelvyBG* swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-999);
                    this->addChild(swelvyBG);

                    for (int i = 0; i < 4; ++i) {
                        if (auto newBg = this->template getChildByType<CCScale9Sprite>(i)) {
                            newBg->setColor(ccColor3B{0, 0, 0});
                            newBg->setOpacity(60);
                        } else {
                            log::debug("Background not found or wrong type at index {}", i);
                        }
                    }
                }
            }
        }
    }
};

// Geode

ADD_TAG("geode.loader/ModsLayer");
class $nodeModify(ModsLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
                if (Mod::get()->getSettingValue<bool>("geode.loader/ModsLayer")) {
                    if (!(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme"))) {
                        /*
                        GeodeInPauseMenu does this and this only to support that mod
                        https://github.com/hiimjasmine00/GeodeInPauseMenu/blob/1ad050e65ba4d0d06993334d974f126ebef96953/src/classes/ModsLayerWrapper.cpp#L28
                        */
                        removeChildByID("bg");
                        removeChildByID("SwelvyBG");
                        SwelvyBG* swelvyBG = SwelvyBG::create();
                        swelvyBG->setZOrder(-1);
                        swelvyBG->setID("SwelvyBG"); // spoof for GeodeInPauseMenu
                        addChild(swelvyBG);
                    }
            }
        }
    }
};

// arcticwoof.rated_layouts

ADD_TAG("arcticwoof.rated_layouts/RLMenuLayer");
SET_SWELVY_SPRITE(RLMenuLayer, "arcticwoof.rated_layouts/RLMenuLayer");

ADD_TAG("arcticwoof.rated_layouts/RLLevelBrowserLayer");
SET_SWELVY_SPRITE(RLLevelBrowserLayer, "arcticwoof.rated_layouts/RLLevelBrowserLayer");

ADD_TAG("arcticwoof.rated_layouts/RLLeaderboardLayer");
SET_SWELVY_SPRITE(RLLeaderboardLayer, "arcticwoof.rated_layouts/RLLeaderboardLayer");

ADD_TAG("arcticwoof.rated_layouts/RLGauntletSelectLayer");
SET_SWELVY_SPRITE(RLGauntletSelectLayer, "arcticwoof.rated_layouts/RLGauntletSelectLayer");

ADD_TAG("arcticwoof.rated_layouts/RLGauntletLevelsLayer");
SET_SWELVY_SPRITE(RLGauntletLevelsLayer, "arcticwoof.rated_layouts/RLGauntletLevelsLayer");

ADD_TAG("arcticwoof.rated_layouts/RLSpireLayer");
SET_SWELVY_SPRITE(RLSpireLayer, "arcticwoof.rated_layouts/RLSpireLayer");

ADD_TAG("arcticwoof.rated_layouts/RLSearchLayer");
class $nodeModify(RLSearchLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
                if (Mod::get()->getSettingValue<bool>("arcticwoof.rated_layouts/RLSearchLayer")) {
                    for (auto* child : CCArrayExt<CCNode*>(getChildren())) {
                        if (std::string(typeid(*child).name()).find("RepeatingBackground") != std::string::npos) {
                            child->setVisible(false);
                            break;
                        }
                    }

                    SwelvyBG* swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(-10);
                    
                    addChild(swelvyBG);
                }
            }
        }
    }
};

ADD_TAG("arcticwoof.rated_layouts/RLShopLayer");
SET_SWELVY_SPRITE(RLShopLayer, "arcticwoof.rated_layouts/RLShopLayer");

ADD_TAG("arcticwoof.rated_layouts/RLSecretLayer1");
SET_SWELVY_SPRITE(RLSecretLayer1, "arcticwoof.rated_layouts/RLSecretLayer1");

ADD_TAG("arcticwoof.rated_layouts/RLSpireSelectLevelLayer");
SET_SWELVY_SPRITE(RLSpireSelectLevelLayer, "arcticwoof.rated_layouts/RLSpireSelectLevelLayer");

// cvolton.betterinfo

ADD_TAG("cvolton.betterinfo/CustomCreatorLayer");
SET_SWELVY(CustomCreatorLayer, "cvolton.betterinfo/CustomCreatorLayer", "cvolton.betterinfo/background");

ADD_TAG("cvolton.betterinfo/DailyViewLayer");
SET_SWELVY(DailyViewLayer, "cvolton.betterinfo/DailyViewLayer", "cvolton.betterinfo/background");

ADD_TAG("cvolton.betterinfo/LeaderboardViewLayer");
SET_SWELVY(LeaderboardViewLayer, "cvolton.betterinfo/LeaderboardViewLayer", "cvolton.betterinfo/background");

ADD_TAG("cvolton.betterinfo/LevelSearchViewLayer");
SET_SWELVY(LevelSearchViewLayer, "cvolton.betterinfo/LevelSearchViewLayer", "cvolton.betterinfo/background");

ADD_TAG("cvolton.betterinfo/RewardGroupLayer");
SET_SWELVY(RewardGroupLayer, "cvolton.betterinfo/RewardGroupLayer", "cvolton.betterinfo/background");

ADD_TAG("cvolton.betterinfo/RewardViewLayer");
SET_SWELVY(RewardViewLayer, "cvolton.betterinfo/RewardViewLayer", "cvolton.betterinfo/background");

// dankmeme.globed2

ADD_TAG("dankmeme.globed2/GlobedLevelListLayer");
SET_SWELVY_WITH_NAMESPACE(globed, GlobedLevelListLayer, "dankmeme.globed2/GlobedLevelListLayer", "background");

ADD_TAG("dankmeme.globed2/GlobedMenuLayer");
SET_SWELVY_WITH_NAMESPACE(globed, GlobedMenuLayer, "dankmeme.globed2/GlobedMenuLayer", "background");

ADD_TAG("dankmeme.globed2/GlobedServersLayer");
SET_SWELVY_WITH_NAMESPACE(globed, GlobedServersLayer, "dankmeme.globed2/GlobedServersLayer", "background");

ADD_TAG("dankmeme.globed2/SettingsLayer");
SET_SWELVY_WITH_NAMESPACE(globed, SettingsLayer, "dankmeme.globed2/SettingsLayer", "background");

// delivel.level-grind

ADD_TAG("delivel.level-grind/CreatorLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, CreatorLayer, "delivel.level-grind/CreatorLayer");

ADD_TAG("delivel.level-grind/CustomBrowserLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, CustomBrowserLayer, "delivel.level-grind/CustomBrowserLayer");

ADD_TAG("delivel.level-grind/GrindPacksLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, GrindPacksLayer, "delivel.level-grind/GrindPacksLayer");

ADD_TAG("delivel.level-grind/MainLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, MainLayer, "delivel.level-grind/MainLayer");

ADD_TAG("delivel.level-grind/PetLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, PetLayer, "delivel.level-grind/PetLayer");

ADD_TAG("delivel.level-grind/SettingsLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, SettingsLayer, "delivel.level-grind/SettingsLayer");

ADD_TAG("delivel.level-grind/SuggestionsLayer");
SET_SWELVY_SPRITE_WITH_NAMESPACE(levelgrind, SuggestionsLayer, "delivel.level-grind/SuggestionsLayer");

// gdcpteam.challenge-list

ADD_TAG("gdcpteam.challenge-list/GDCPListLayer");
SET_SWELVY(GDCPListLayer, "gdcpteam.challenge-list/GDCPListLayer", "background");

// gdutilsdevs.gdutils

ADD_TAG("gdutilsdevs.gdutils/MoreLeaderboards");
SET_SWELVY_SPRITE(MoreLeaderboards, "gdutilsdevs.gdutils/MoreLeaderboards");

// geode.texture-loader

ADD_TAG("geode.texture-loader/PackSelectLayer");
SET_SWELVY(PackSelectLayer, "geode.texture-loader/PackSelectLayer", "background");

// hiimjustin000.integrated_demonlist

ADD_TAG("hiimjustin000.integrated_demonlist/IDListLayer");
SET_SWELVY_SPRITE(IDListLayer, "hiimjustin000.integrated_demonlist/IDListLayer");

ADD_TAG("hiimjustin000.integrated_demonlist/IDPackLayer");
SET_SWELVY_SPRITE(IDPackLayer, "hiimjustin000.integrated_demonlist/IDPackLayer");

// km7dev.gdps-switcher

ADD_TAG("km7dev.gdps-switcher/ServerSwitchLayer");
SET_SWELVY(ServerSwitchLayer, "km7dev.gdps-switcher/ServerSwitchLayer", "background");

// lblazen.gdps_hub

ADD_TAG("lblazen.gdps_hub/GDPSHubLayer");
class $nodeModify(MyGDPSHubLayer, GDPSHubLayer) {
    void modify() {
        if (Mod::get()->getSettingValue<std::string>("background-type") != "Disabled") {
            if (Mod::get()->getSettingValue<bool>("lblazen.gdps_hub/GDPSHubLayer")) {
                if (auto bg = this->getChildByID("background")) {
                    bg->setVisible(false);
                    this->getChildByID("swelvy-node")->setVisible(false);
                    SwelvyBG* swelvyBG = SwelvyBG::create();
                    swelvyBG->setZOrder(bg->getZOrder() - 1);
                    this->addChild(swelvyBG);
                }
            }
        }
    }
};

// minemaker0430.gddp_integration

ADD_TAG("minemaker0430.gddp_integration/DPLayer");
SET_SWELVY(DPLayer, "minemaker0430.gddp_integration/DPLayer", "bg");

ADD_TAG("minemaker0430.gddp_integration/DPListLayer");
SET_SWELVY(DPListLayer, "minemaker0430.gddp_integration/DPListLayer", "bg");

ADD_TAG("minemaker0430.gddp_integration/DPSearchLayer");
SET_SWELVY(DPSearchLayer, "minemaker0430.gddp_integration/DPSearchLayer", "bg");

ADD_TAG("minemaker0430.gddp_integration/RecommendedLayer");
SET_SWELVY(RecommendedLayer, "minemaker0430.gddp_integration/RecommendedLayer", "bg");

ADD_TAG("minemaker0430.gddp_integration/RouletteSafeLayer");
SET_SWELVY(RouletteSafeLayer, "minemaker0430.gddp_integration/RouletteSafeLayer", "bg");

// omgrod.geodify

ADD_TAG("omgrod.geodify/GYSettingSelectLayer");

// omgrod.thatdarncoin

ADD_TAG("omgrod.thatdarncoin/CreditsLayer");
SET_SWELVY_SPRITE(CreditsLayer, "omgrod.thatdarncoin/CreditsLayer");

ADD_TAG("omgrod.thatdarncoin/ElderLayer");
SET_SWELVY_SPRITE(ElderLayer, "omgrod.thatdarncoin/ElderLayer");

// teamtcm.geometry-dash-odyssey

ADD_TAG("teamtcm.geometry-dash-odyssey/OdysseyComicLayer");
SET_SWELVY(OdysseyComicLayer, "teamtcm.geometry-dash-odyssey/OdysseyComicLayer", "teamtcm.geometry-dash-odyssey/background");

ADD_TAG("teamtcm.geometry-dash-odyssey/OdysseySelectLayer");
SET_SWELVY_SPRITE(OdysseySelectLayer, "teamtcm.geometry-dash-odyssey/OdysseySelectLayer");

// timestepyt.secretlayer6

ADD_TAG("timestepyt.secretlayer6/SecretLayer6R");
SET_SWELVY_SPRITE(SecretLayer6R, "timestepyt.secretlayer6/SecretLayer6R");

// uproxide.textures

ADD_TAG("uproxide.textures/TextureWorkshopLayer");
SET_SWELVY(TextureWorkshopLayer, "uproxide.textures/TextureWorkshopLayer", "background");
