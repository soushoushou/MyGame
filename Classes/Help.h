#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 

USING_NS_CC;
using namespace ui;


//用户帮助场景
class Help :public Layer
{
public:
	class MyScrollView : public ScrollView
	{
	public:
		static MyScrollView* create()
		{
			MyScrollView* widget = new (std::nothrow) MyScrollView();
			if (widget && widget->init())
			{
				widget->autorelease();
				return widget;
			}
			CC_SAFE_DELETE(widget);
			return nullptr;
		}
		void setMinPos(int pos){ m_minPos = pos; }
		bool onTouchBegan(Touch *touch, Event *unusedEvent);
		void onTouchMoved(Touch *touch, Event *unusedEvent);
		void onTouchEnded(Touch *touch, Event *unusedEvent);
		void onTouchCancelled(Touch *touch, Event *unusedEvent);
	private:
		int m_minPos;
	};
	Help();
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(Help);
	virtual ~Help();
	static void onBtnTouch(Ref *pSender, Widget::TouchEventType type);

private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	bool initInstruction();
	void flushNoticeLabel(float delta);			//重绘公告
	MyScrollView* scrollView;
	Label* label_notice;
    Label* label;
};

