#include "SwelvyBG.hpp"
#include "ccTypes.h"
#include <Geode/loader/Mod.hpp>
#include <random>

bool SwelvyBG::init(float widthmult, float hightmult, float minspeed, float maxspeed) {
    if (!CCNode::init())
        return false;

    this->setID("SwelvyBG");

    auto winSize = CCDirector::get()->getWinSize();
    this->setContentSize(winSize);
    this->setAnchorPoint({ 0.f, 0.f });
    this->setID("swelvy-background"_spr);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sign(0, 1);
    std::uniform_real_distribution<float> dis(3.f, 9.f);

    float y = m_obContentSize.height + 5;
    int idx = 0;

    bool enableColor = Mod::get()->getSettingValue<bool>("color-enable");
    log::debug("Color feature enabled: {}", enableColor);

    auto createLayer = [&](ccColor3B color, const char* texturePath) {
        ccColor3B adjustedColor = color;

        float speed = dis(gen);
        if (sign(gen) == 0) {
            speed = -speed;
        }
        ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};

        auto sprite = CCSprite::create(texturePath);
        if (!sprite) {
            log::debug("Failed to load texture: {}", texturePath);
            return;
        }

        auto rect = sprite->getTextureRect();
        sprite->setUserObject("width", CCFloat::create(rect.size.width * widthmult));
        rect.size = CCSize{winSize.width * widthmult, rect.size.height * hightmult};

        std::string layerID = fmt::format("layer-{}", idx);
        sprite->setID(layerID);
        sprite->getTexture()->setTexParameters(&params);
        sprite->setTextureRect(rect);
        sprite->setAnchorPoint({ 0, 1 });
        sprite->setContentSize({ winSize.width * widthmult, sprite->getContentSize().height });
        sprite->setColor(adjustedColor);
        sprite->setPosition({ 0, y });
        sprite->schedule(schedule_selector(SwelvyBG::updateSpritePosition));
        sprite->setUserObject("speed", CCFloat::create(speed));
        this->addChild(sprite);

        log::debug("Created layer {} with color ({}, {}, {})", layerID, adjustedColor.r, adjustedColor.g, adjustedColor.b);

        y -= m_obContentSize.height / 6;
        idx += 1;
    };

    if (enableColor) {
        for (auto layer : std::initializer_list<std::pair<ccColor3B, const char*>> {
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-0"), "geode.loader/swelve-layer3.png" },
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-1"), "geode.loader/swelve-layer0.png" },
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-2"), "geode.loader/swelve-layer1.png" },
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-3"), "geode.loader/swelve-layer2.png" },
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-4"), "geode.loader/swelve-layer1.png" },
            { Mod::get()->getSettingValue<cocos2d::ccColor3B>("color-5"), "geode.loader/swelve-layer0.png" },
        }) {
            createLayer(layer.first, layer.second);
        }
    } else {
        log::debug("Color feature disabled. Using default colors.");
        for (auto layer : std::initializer_list<std::pair<ccColor3B, const char*>> {
            { ccc3(244, 212, 142), "geode.loader/swelve-layer3.png" },
            { ccc3(245, 174, 125), "geode.loader/swelve-layer0.png" },
            { ccc3(236, 137, 124), "geode.loader/swelve-layer1.png" },
            { ccc3(213, 105, 133), "geode.loader/swelve-layer2.png" },
            { ccc3(173, 84, 146), "geode.loader/swelve-layer1.png" },
            { ccc3(113, 74, 154), "geode.loader/swelve-layer0.png" },
        }) {
            createLayer(layer.first, layer.second);
        }
    }

    return true;
}

void SwelvyBG::updateSpritePosition(float dt) {
    auto speedObj = typeinfo_cast<CCFloat*>(this->getUserObject("speed"));
    auto widthObj = typeinfo_cast<CCFloat*>(this->getUserObject("width"));

    if (!speedObj || !widthObj) {
        log::debug("Sprite missing required user objects: speed or width");
        return;
    }

    float speed = speedObj->getValue();
    float width = widthObj->getValue();

    auto sprite = typeinfo_cast<CCSprite*>(this);
    if (!sprite) {
        log::debug("Failed to cast object to CCSprite in updateSpritePosition");
        return;
    }

    auto rect = sprite->getTextureRect();
    float dX = rect.origin.x - speed * dt;
    if (dX >= std::abs(width)) {
        dX = 0;
    }

    rect.origin = CCPoint{ dX, 0 };
    sprite->setTextureRect(rect);

    // log::debug("Updated sprite {} position: dX={}, speed={}, width={}", sprite->getID(), dX, speed, width);
}

SwelvyBG* SwelvyBG::create(float widthmult, float hightmult, float minspeed, float maxspeed) {
    auto ret = new SwelvyBG();
    if (ret->init(widthmult, hightmult, minspeed, maxspeed)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    log::debug("Failed to create SwelvyBG instance");
    return nullptr;
}
