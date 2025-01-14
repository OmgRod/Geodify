#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

#include "GYModTile.hpp"
#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/ui/GeodeUI.hpp"

using namespace geode::prelude;

void GYModTile::viewMod(CCObject* sender) {
    log::debug("Viewing mod: {}", this->getTag());
}

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
    this->setTag(tag);

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

    auto sprite = CCNode::create();

    if (modID != "gd") {
        if (modID == "geode.loader") {
            sprite = CCSprite::create("geodeLogo.png"_spr);
        } else {
            sprite = geode::createServerModLogo(modID);
        }
    } else {
        sprite = CCSprite::create("gdLogo.png"_spr);
    }

    sprite->setScale((winSize.height * 0.225) / sprite->getContentSize().height);
    sprite->setPosition({ this->getContentSize().width / 2, this->getContentSize().height / 2 + (this->getContentSize().height * 0.1f) });

    this->addChild(sprite);

    auto menu = CCMenu::create();
    menu->setAnchorPoint({ 0, 0 });
    menu->setContentSize({ this->getContentSize().width, this->getContentSize().height });
    menu->setPosition({ 0, 0 });

    auto btn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("View"),
        this,
        menu_selector(GYModTile::viewMod)
    );
    btn->setPosition({ this->getContentSize().width / 2, winSize.height * 0.075f });
    btn->setScale(0.8f);

    menu->addChild(btn);
    this->addChild(menu);
    
    return true;
}