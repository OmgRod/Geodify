#include <Geode/Geode.hpp>

#include "GYModTile.hpp"

using namespace geode::prelude;

GYModTile* GYModTile::create() {
    GYModTile* ret = new GYModTile();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GYModTile::init() {
    if (!CCLayer::init())
        return false;
    
    setMouseEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setContentSize({ winSize.width * 0.325f, winSize.height * 0.4f });

    // GJ_square04.png - The purple one
    auto bg = CCScale9Sprite::create("GJ_square04.png");
    bg->setContentSize(this->getContentSize());
    bg->setAnchorPoint({ 0.f, 0.f});
    this->addChild(bg);
    
    return true;
}