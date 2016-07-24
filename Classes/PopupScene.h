#ifndef TestCpp_PopupScene_h
#define TestCpp_PopupScene_h

#include "cocos2d.h"
#include "ui/UICheckBox.h"
USING_NS_CC;
using namespace cocos2d;
using namespace ui;
class Popup : public CCLayer {
public:
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(Popup);

	void popupLayer();

	void menuCallback(CCObject* pSender);
	void buttonCallback(CCNode* pSender);
	//void selectedEvent(Object* pSender, CheckBoxEventType type);
};

#endif
