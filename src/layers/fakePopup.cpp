#include "fakePopup.hpp"
FakePopup *FakePopup::create(cocos2d::CCLayer *fake) {
	auto ret = new FakePopup();
	if (ret->init(fake)) {
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}
void FakePopup::close() {
	onClose(nullptr);
}
bool FakePopup::init(cocos2d::CCLayer *layer) {
	if (!geode::Popup::init({0, 0}))
		return false;

	setID("FakeLayerWrapper");

	m_noElasticity = true;

	if (m_mainLayer)
		m_mainLayer->removeFromParent();

	m_mainLayer = layer;
	addChild(layer);
	return true;
};
void FakePopup::keyDown(cocos2d::enumKeyCodes key, double timestamp) {
	m_mainLayer->keyDown(key, timestamp);
}