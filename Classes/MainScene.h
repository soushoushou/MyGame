#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "UserProfileUI.h"
#include "NetworkManger.h"
USING_NS_CC;
using namespace ui;

//登录后的主菜单场景
class MainScene :public Layer
{
public:
	MainScene(unsigned long long playerID);
	static Scene* scene(unsigned long long playerID);
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual ~MainScene();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
	void buttonCallback(CCNode* pSender);
private:
	bool initBackground();
	bool initButtons();
	bool initNotice();
	bool initPlayerProfile();					
	void flushNoticeLabel(float delta);			//重绘公告
	static MainScene* createMainScene(unsigned long long  playerID);

private:
	LabelTTF* m_pNoticeLabel;
	UserProfileUI* m_pUser;
	Sprite* m_spRoundRectInNotice;		

	unsigned long long m_playerID;
	string m_strPlayerName;
	int m_currentDiamond;
	int m_currentMoney;
};



