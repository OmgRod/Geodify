#include "SwelvyBG.hpp"
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

    bool enableColor = Mod::get()->getSettingValue<bool>("enable-color");

    auto createLayer = [&](ccColor3B color, const char* texturePath) {
        ccColor3B adjustedColor = color;

        if (enableColor) {
            // Construct the setting key dynamically
            std::string settingKey = "color-" + std::to_string(idx);
            auto colorSetting = Mod::get()->getSettingValue<std::string>(settingKey);

            if (!colorSetting.empty()) {
                unsigned int r, g, b;
                if (sscanf(colorSetting.c_str(), "%u,%u,%u", &r, &g, &b) == 3) {
                    adjustedColor = {
                        static_cast<GLubyte>(std::min(255u, r)),
                        static_cast<GLubyte>(std::min(255u, g)),
                        static_cast<GLubyte>(std::min(255u, b))
                    };
                }
            }
        }

        float speed = dis(gen);
        if (sign(gen) == 0) {
            speed = -speed;
        }
        ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};

        auto sprite = CCSprite::create(texturePath);
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
    auto speed = typeinfo_cast<CCFloat*>(this->getUserObject("speed"))->getValue();
    auto width = typeinfo_cast<CCFloat*>(this->getUserObject("width"))->getValue();

    auto sprite = typeinfo_cast<CCSprite*>(this);
    auto rect = sprite->getTextureRect();

    float dX = rect.origin.x - speed * dt;
    if (dX >= std::abs(width)) {
        dX = 0;
    }

    rect.origin = CCPoint{ dX, 0 };
    sprite->setTextureRect(rect);
}

SwelvyBG* SwelvyBG::create(float widthmult, float hightmult, float minspeed, float maxspeed) {
    auto ret = new SwelvyBG();
    if (ret->init(widthmult, hightmult, minspeed, maxspeed)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}