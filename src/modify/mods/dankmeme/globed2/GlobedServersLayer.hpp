#pragma once
using namespace geode::prelude;
#include <Geode/Geode.hpp>
#include "../../../../SwelvyBG.hpp"
static bool GlobedServersLayerInit(CCLayer* _This) {

        if (CCNode* bg = typeinfo_cast<CCNode*>(_This->getChildren()->objectAtIndex(1)) ) {
			bg->setVisible(false);
		}

		SwelvyBG* swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-1);
		swelvyBG->setID("swelvy-background");

    	_This->addChild(swelvyBG);
        return true;
}