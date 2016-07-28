#pragma once
#include <string>
#include "cocos2d.h"
#include "toolFunctions.h"
using namespace std;
USING_NS_CC;

class User
{
public:
	User();
	User(int x, int y, const string name, const string level);
	bool setProfile(int x, int y, const string name, const string level);
	Sprite* getHeadSprite();
	LabelTTF* getPlayerName();
	LabelTTF* getLevel();
	~User();
protected:
	string m_strPlayerName;			//用户昵称
	string m_strLevel;				//用户等级
	Sprite* m_spOutline;			//边框精灵
	Sprite* m_spHead;				//头像精灵
	LabelTTF* m_lblPlayerName;		//用户昵称label
	LabelTTF* m_lblLevel;			//等级label
	int m_nExp;						//经验值
};