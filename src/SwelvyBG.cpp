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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> sign(0, 1);
    std::uniform_real_distribution<float> dis(3.f, 9.f);

    float y = m_obContentSize.height + 5;
    int idx = 0;

    // Retrieve the color offset setting
    auto mod = Mod::get();
    ccColor3B colorOffset = { 0, 0, 0 }; // Default offset is zero (no adjustment)
    bool enableColor = false;

    if (mod) {
        enableColor = mod->getSettingValue<bool>("enable-color");
        if (enableColor) {
            auto colorSetting = mod->getSettingValue<std::string>("color");
            if (!colorSetting.empty()) {
                sscanf(colorSetting.c_str(), "%hhu,%hhu,%hhu", &colorOffset.r, &colorOffset.g, &colorOffset.b);
            }
        }
    }

    for (auto layer : std::initializer_list<std::pair<ccColor3B, const char*>> {
        { ccc3(244, 212, 142), "geode.loader/swelve-layer3.png" },
        { ccc3(245, 174, 125), "geode.loader/swelve-layer0.png" },
        { ccc3(236, 137, 124), "geode.loader/swelve-layer1.png" },
        { ccc3(213, 105, 133), "geode.loader/swelve-layer2.png" },
        { ccc3(173, 84,  146), "geode.loader/swelve-layer1.png" },
        { ccc3(113, 74,  154), "geode.loader/swelve-layer0.png" },
    }) {
        ccColor3B adjustedColor = layer.first;

        if (enableColor) {
            // Apply the color offset
            adjustedColor = {
                static_cast<GLubyte>(std::min(255, layer.first.r + colorOffset.r)),
                static_cast<GLubyte>(std::min(255, layer.first.g + colorOffset.g)),
                static_cast<GLubyte>(std::min(255, layer.first.b + colorOffset.b))
            };
        }

        float speed = dis(gen);
        if (sign(gen) == 0) {
            speed = -speed;
        }
        ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};

        auto sprite = CCSprite::create(layer.second);
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