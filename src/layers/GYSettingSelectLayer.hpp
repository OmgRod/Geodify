#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class GYSettingSelectLayer : public CCLayer {
  public:
	virtual void keyBackClicked();
	static CCScene *scene();
	static GYSettingSelectLayer *create();
	static geode::Popup *popup();
	bool init();
	void settingsBtn(CCObject *sender);
	void colorPopup(CCObject *sender);
	void backWrapper(CCObject *sender);
	void openNormalSettings(CCObject *sender);

  protected:
	bool m_isPopup = false;
};