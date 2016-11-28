#pragma once
#include "cocos2d.h"
#include <vector>
#include "NiuPoker.h"
#include "SiteManager.h"
#include <utility>
using namespace std;
USING_NS_CC;

//玩家-扑克
struct S_PlayerPorker
{
	S_PlayerPorker() :playerID(0), vecPorkerIndex(5, -1){}
	unsigned long long playerID;			//玩家ID
	vector<int> vecPorkerIndex;				//玩家对应的5张牌
};

class PorkerManager
{
public:
	PorkerManager(Node* parent,SiteManager* pSite);
	virtual ~PorkerManager();
	void SendPorker(const vector<S_PlayerPorker>& porkers);			//发牌
	void ShowAllPorkers();
	void EmptyAllPorkers();
	bool RunActions();												//运行发牌动画，返回true则代表所有动画结束
	vector<NiuPoker*> GetMePlayerPoker();							//返回游戏中ME玩家的5张牌
	
private:
	bool createPokers();
	NiuPoker* selectPoker(int huaSe, int num);
	/** 发牌移动动画 */
	void MovePk(NiuPlayer* play, NiuPoker* pk);				
private:

	class PokerAction:public Ref
	{
	public:
		void updatePokerPos(Node* pSender, void* pData);
	};
	__Array* m_arrPokers;				//52张牌
	Node* m_pParent;
	SiteManager* m_pSitManager;
	vector<pair<NiuPoker*, Sequence*> > m_poker2Actions;			//扑克和动画的映射
	int m_currentPokerActionIndex;
public:
    static vector<NiuPoker*> m_touchPokers;
};

vector<NiuPoker*> PorkerManager::m_touchPokers;

