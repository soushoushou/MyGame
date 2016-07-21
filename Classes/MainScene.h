#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
USING_NS_CC;
using namespace ui;


//登录后的主菜单场景
class MainScene :public Layer
{
public:
	MainScene();
	static CCScene* scene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	virtual void onEnter();
	virtual void onExit();
	virtual ~MainScene();
	static void onBtnTouch(Ref *pSender, Widget::TouchEventType type);		
	void update(float delta);

private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	void flushNoticeLabel(float delta);			//重绘公告

private:
	LabelTTF* m_pNoticeLabel;
};

