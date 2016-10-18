#pragma once
#include "Global.h"
#include "cocos2d.h"
#include "UserProfileUI.h"
#include "NiuPlayer.h"
#include <vector>
using namespace std;
USING_NS_CC;


//管理游戏中的玩家座位
class SiteManager
{
public:
	SiteManager(Node* parent);
	virtual ~SiteManager();

	//玩家找个位置坐下
	bool joinSite(unsigned long long playerID, string playerName, int diamond, int money);
	//离开座位
	bool leaveSite(unsigned long long playerID);
	//设置倍数
	bool setMultiple(unsigned long long playerID);
	//设置庄家
	bool setZhuangJia(unsigned long long playerID);

private:
	struct PlayerAndProfilePos
	{
		Point playerPos;
		Point profilePos;
		int profileType;		//0为水平，1为垂直
	};

private:
	vector<NiuPlayer*> m_inRoomPlayer;
	vector<PlayerAndProfilePos> m_playerProfileInfo;			//位置信息
	vector<IUserProfileUIInGame*> m_pUserProfileVecs;			//头像UI，第0个是当前玩家头像
	vector<int> m_playerInRoom;									//房间里的坑位，0表示没人坐，1表示有人坐
	vector<unsigned long long> m_inRoomPlayerID;				//0为不存在
	
	Node* m_pParent;
};

