#pragma once

#include <Geode/ui/General.hpp>

using namespace geode::prelude;

#define SET_SWELVY(layer, setting, backgroundID)\
class $nodeModify(my##layer, layer) {\
    void modify() {\
        if (Mod::get()->getSettingValue<bool>(setting)) {\
            if (auto bg = getChildByID(backgroundID)) {\
                bg->setVisible(false);\
                SwelvyBG* swelvyBG = SwelvyBG::create();\
                swelvyBG->setZOrder(-999);\
                addChild(swelvyBG);\
            }\
        }\
    }\
}

#define SET_SWELVY_SPRITE(layer, setting)\
class $nodeModify(my##layer, layer) {\
    void modify() {\
        if (Mod::get()->getSettingValue<bool>(setting)) {\
            if (auto bg = getChildByType<CCSprite>(0)) {\
                bg->setVisible(false);\
                SwelvyBG* swelvyBG = SwelvyBG::create();\
                swelvyBG->setZOrder(-999);\
                addChild(swelvyBG);\
            }\
        }\
    }\
}


#define SET_SWELVY_SPRITE_NOBG(layer, setting) \
class $nodeModify(my##layer, layer) { \
    void modify() { \
        int lowestZ = INT_MAX;\
        CCNode* node = nullptr;\
        CCObject* obj = nullptr; \
        CCARRAY_FOREACH(getChildren(), obj) { \
            if (node) { \
                lowestZ = std::min(lowestZ, node->getZOrder()); \
            } \
        } \
        \
        if (Mod::get()->getSettingValue<bool>(setting)) { \
            SwelvyBG* swelvyBG = SwelvyBG::create(); \
            swelvyBG->setZOrder(lowestZ - 1);\
            addChild(swelvyBG); \
        } \
    } \
}

class SwelvyBG : public CCNode {
protected:
    bool init(float widthmult, float heightmul, float minspeed, float maxspeed);

    void updateSpritePosition(float dt);

public:
    static SwelvyBG* create(float widthmult = 1, float heightmul = 1, float minspeed = -1000, float maxspeed = 10000);
};
