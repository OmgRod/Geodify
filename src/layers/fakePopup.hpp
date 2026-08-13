#include <Geode/Geode.hpp>
#include <Geode/Loader.hpp>
class FakePopup : public geode::Popup {
  public:
	static FakePopup *create(cocos2d::CCLayer *fake);
	void close();
  protected:
	bool init(cocos2d::CCLayer *layer);
    //void registerWithTouchDispatcher();
    void keyDown(cocos2d::enumKeyCodes key, double timestamp);
};