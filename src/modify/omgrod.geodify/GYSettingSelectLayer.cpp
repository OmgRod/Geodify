// #include <Geode/Geode.hpp>
// #include "../../SwelvyBG.hpp"
// #include <HookClass.hpp> 

// using namespace geode::prelude;
// HookClass(GYSettingSelectLayer) {
//     if (Mod::get()->getSettingValue<bool>("external-mods")) {
//         if (auto bg = this->getChildByID("background")) {
//             bg->setVisible(false);
//         }

//         SwelvyBG* swelvyBG = SwelvyBG::create();
//         swelvyBG->setZOrder(-99999);
//         swelvyBG->setID("swelvy-background");
//         this->addChild(swelvyBG);
//     }
// }