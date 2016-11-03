#pragma once
#include "Global.h"
#include "cocos2d.h"
#include "UserProfileUI.h"
#include "NiuPlayer.h"
#include <vector>
#include <mutex>
#include <array>
using namespace std;
USING_NS_CC;

class PorkerManager;

//管理游戏中的玩家座位
class SiteManager
{
public:
	SiteManager(Node* parent,unsigned long long currentPlayerID);
	virtual ~SiteManager();

	//玩家找个位置坐下
	bool joinSite(unsigned long long playerID, string playerName, int diamond, int money);
	//离开座位
	bool leaveSite(unsigned long long playerID);
	//设置倍数
	bool setMultiple(unsigned long long playerID, int multiple);
	//显示倍数
	bool showMultiple(unsigned long long playerID,bool isShow = true);
	//设置庄家
	bool showZhuangJia(unsigned long long playerID);
	//显示准备
	bool showReady(unsigned long long playerID, bool isShow = true);


private:
	//玩家和头像位置信息
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0为水平，1为垂直
	};

private:
	array<NiuPlayer*,5> m_inRoomPlayer;
	array<PlayerAndProfilePos,5> m_playerProfileInfo;			//位置信息
	array<IUserProfileUIInGame*,5> m_pUserProfileVecs;			//头像UI，第0个是当前玩家头像
	array<int,5> m_playerInRoom;									//房间里的坑位，0表示没人坐，1表示有人坐
	array<unsigned long long,5> m_inRoomPlayerID;				//0为不存在

	unsigned long long m_currentPlayerID;						//自己的ID

	Node* m_pParent;

	friend class PorkerManager;
	mutex m_lock;
};

