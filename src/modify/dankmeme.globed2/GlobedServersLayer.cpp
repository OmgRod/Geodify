#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp" 
using namespace geode::prelude;
Viper_Hookclass(GlobedServersLayer) {
        if (CCNode* bg = typeinfo_cast<CCNode*>(this->getChildren()->objectAtIndex(1)) ) {
            bg->setVisible(false);
        }

        SwelvyBG* swelvyBG = SwelvyBG::create();
        swelvyBG->setZOrder(-1);
        swelvyBG->setID("swelvy-background");
        this->addChild(swelvyBG);
}