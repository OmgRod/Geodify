#include <Geode/Geode.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include <Geode/Loader.hpp>

#include "GYModTile.hpp"
#include "GYModSettingsPopup.hpp"

using namespace geode::prelude;

void GYModTile::viewMod(CCObject* sender) {
    log::debug("Viewing mod: {}", this->m_modID);
    GYModSettingsPopup::create(this->m_modName, this->m_modAuthor, this->m_modID)->show();
}

GYModTile* GYModTile::create(std::string modName, std::string modAuthor, std::string modID) {
    GYModTile* ret = new GYModTile();
    if (ret && ret->init(modName, modAuthor, modID)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GYModTile::init(std::string modName, std::string modAuthor, std::string modID) {
    if (!CCLayer::init())
        return false;

    this->m_modID = modID;
    this->m_modName = modName;
    this->m_modAuthor = modAuthor;
    
    setMouseEnabled(true);

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setContentSize({ winSize.width * 0.325f, winSize.height * 0.5f });

    // GJ_square04.png - The purple one
    auto bg = CCScale9Sprite::create("GJ_square04.png");
    bg->setContentSize(this->getContentSize());
    bg->setAnchorPoint({ 0.f, 0.f});
    this->addChild(bg);

    auto modNameText = CCLabelBMFont::create(modName.c_str(), "bigFont.fnt");
    modNameText->setPosition({ this->getContentSize().width / 2, this->getContentSize().height - winSize.height * 0.05f });
    float maxWidth = this->getContentSize().width * 0.8f;
    float scale = (modNameText->getContentSize().width > maxWidth) ? (this->getContentSize().width * 0.7f) / modNameText->getContentSize().width : 0.5f;
    modNameText->setScale(std::min(scale, 0.5f));
    bg->addChild(modNameText);

    auto modAuthorText = CCLabelBMFont::create(fmt::format("By {}", modAuthor).c_str(), "goldFont.fnt");
    modAuthorText->setPosition({ this->getContentSize().width / 2, this->getContentSize().height - winSize.height * 0.35f });
    scale = (modAuthorText->getContentSize().width > maxWidth) ? (this->getContentSize().width * 0.7f) / modAuthorText->getContentSize().width : 0.5f;
    modAuthorText->setScale(std::min(scale, 0.5f));
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