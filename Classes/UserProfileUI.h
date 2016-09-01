#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui/CocosGUI.h" 
using namespace std;
USING_NS_CC;
using namespace ui;

//基类
class UserProfileUI:public Ref
{
public:
	UserProfileUI(Node* pParent);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond,const int coin) = 0;
	virtual ~UserProfileUI();
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

//用于游戏中的头像接口
class IUserProfileUIInGame : public UserProfileUI
{
public:
	IUserProfileUIInGame(Node* pParent) :UserProfileUI(pParent),m_spBankerFrame(0), m_lblMultiple(0){}
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple) = 0;
	virtual void showMultiple(bool isShow = true) = 0;												//显示倍数
	virtual void showBanker(bool isShow = true) = 0;													//显示庄家框
	virtual ~IUserProfileUIInGame(){}
protected:
	Sprite* m_spBankerFrame;
	LabelTTF* m_lblMultiple;
};

//竖向用户头像UI，用于游戏中
class VerticalUserProfileUI : public IUserProfileUIInGame
{
public:
	static IUserProfileUIInGame* create(Node* pParent);
	VerticalUserProfileUI(Node* pParent);
	//VerticalUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple);
	virtual void showMultiple(bool isShow = true);													//显示倍数
	virtual void showBanker(bool isShow = true);													//显示庄家框
};

//横向用户头像UI，用于游戏中
class HerizelUserProfileUI : public IUserProfileUIInGame
{
public:
	static IUserProfileUIInGame* create(Node* pParent);
	HerizelUserProfileUI(Node* pParent);
	//HerizelUserProfileUI(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin){ return true; }
	virtual bool setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin, const int multiple);
	virtual void showMultiple(bool isShow = true);												//显示倍数
	virtual void showBanker(bool isShow = true);													//显示庄家框
};

class UserProfileUIInMainScene : public UserProfileUI
{
public:
	static UserProfileUI* create(Node* pParent);
	UserProfileUIInMainScene(Node* pParent);
	UserProfileUIInMainScene(Node* pParent, Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	virtual bool setProfile(Vec2 pos, const string headFileName, const string name, const int diamond, const int coin);
	void onAddBtnTouch(Ref *pSender, Widget::TouchEventType type);
	virtual ~UserProfileUIInMainScene();
private:
	Sprite* m_spRoundRect;
	Sprite* m_spRoundRect2;
	Button* m_btnAddDiamond;
	Button* m_btnAddCoin;
	Sprite* m_spDianmond;			//钻石精灵

};

