#include <Geode/Geode.hpp>

#include "GYModTile.hpp"

using namespace geode::prelude;

GYModTile* GYModTile::create(const char *modName, const char *modAuthor, const char *modID, int tag) {
    GYModTile* ret = new GYModTile();
    if (ret && ret->init(modName, modAuthor, modID, tag)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GYModTile::init(const char *modName, const char *modAuthor, const char *modID, int tag) {
    if (!CCLayer::init())
        return false;
    
    setMouseEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setContentSize({ winSize.width * 0.325f, winSize.height * 0.5f });

    // GJ_square04.png - The purple one
    auto bg = CCScale9Sprite::create("GJ_square04.png");
    bg->setContentSize(this->getContentSize());
    bg->setAnchorPoint({ 0.f, 0.f});
    this->addChild(bg);

    auto modNameText = CCLabelBMFont::create(modName, "bigFont.fnt");
    modNameText->setPosition({ this->getContentSize().width / 2, this->getContentSize().height - winSize.height * 0.05f });
    modNameText->setScale(0.5f);
    bg->addChild(modNameText);

    auto modAuthorText = CCLabelBMFont::create(fmt::format("By {}", modAuthor).c_str(), "goldFont.fnt");
    modAuthorText->setPosition({ this->getContentSize().width / 2, this->getContentSize().height - winSize.height * 0.35f });
    modAuthorText->setScale(0.5f);
    bg->addChild(modAuthorText);
    
    return true;
}