#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui/CocosGUI.h" 
using namespace std;
USING_NS_CC;
using namespace ui;

//基类
class UserProfileUI
{
public:
	UserProfileUI(Node* pParent);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond,const int coin) = 0;
	~UserProfileUI();
protected:
	string m_strPlayerName;			//用户昵称
	int m_nCoin;					//金币数量
	int m_nDiamond;					//钻石数量
	LabelTTF* m_lblDiamond;			//钻石数量label
	LabelTTF* m_lblCoin;			//金币数量label
	Sprite* m_spHead;				//头像精灵
	Sprite* m_spFrame;				//框子
	LabelTTF* m_lblPlayerName;		//用户昵称label
	Node* m_pParent;				//父节点
	Sprite* m_spCoin;				//金币精灵
	Sprite* m_spDianmond;			//钻石精灵
};

//竖向用户头像UI，用于游戏中
class VerticalUserProfileUI : public UserProfileUI
{
public:
	VerticalUserProfileUI(Node* pParent);
	VerticalUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
};

//横向用户头像UI，用于游戏中
class HerizelUserProfileUI: public UserProfileUI
{
public:
	HerizelUserProfileUI(Node* pParent);
	HerizelUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
protected:
private:
};

class UserProfileUIInMainScene : public HerizelUserProfileUI
{
public:
	UserProfileUIInMainScene(Node* pParent);
	UserProfileUIInMainScene(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	void onAddBtnTouch(Ref *pSender, Widget::TouchEventType type);
private:
	Sprite* m_spRoundRect;
	Sprite* m_spRoundRect2;
	Button* m_btnAddDiamond;
	Button* m_btnAddCoin;
	Sprite* m_spDianmond;			//钻石精灵

};

