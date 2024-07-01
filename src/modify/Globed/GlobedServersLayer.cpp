
#include <Geode/Geode.hpp>
#include "../../SwelvyBG.hpp"
#include "../../Hooks/Hooker.hpp"
using namespace geode::prelude;
class GlobedServersLayer : public Betterhook::HookBetter {
        void init(CCNode* _This) override {
           if (CCNode* bg = typeinfo_cast<CCNode*>(_This->getChildren()->objectAtIndex(1)) ) {
			bg->setVisible(false);
		}

		SwelvyBG* swelvyBG = SwelvyBG::create();
		swelvyBG->setZOrder(-1);
		swelvyBG->setID("swelvy-background");
    	_This->addChild(swelvyBG);
        };

        const char* PutLayer() const override { return "GlobedServersLayer"; }
    };

REGISTER_Hook(GlobedServersLayer);

        
