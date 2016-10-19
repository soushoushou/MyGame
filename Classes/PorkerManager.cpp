#include "PorkerManager.h"
#include "GamePlayScene.h"

PorkerManager::PorkerManager(Node* parent, SiteManager* pSite) :m_pParent(parent), m_pSitManager(pSite)
{
	createPokers();
}


PorkerManager::~PorkerManager()
{
}

void PorkerManager::MovePk(NiuPlayer* play, NiuPoker* pk)
{
	MoveTo* move;
	__CCCallFuncND* func;
	float time = 0.05;
	play->getArrPk()->addObject(pk);
	move = MoveTo::create(time, play->getPoint());
	func = __CCCallFuncND::create(m_pParent, callfuncND_selector(GamePlayScene::func), play);
	Sequence* sequence = Sequence::create(move, func, NULL);
	pk->runAction(sequence);
}


bool PorkerManager::createPokers()	
{
	bool isRet = false;
	do
	{
		NiuPoker* pk;
		//´´½¨52¸öÅÆ
		for (int i = 1; i <= 4; ++i)
		{
			for (int j = 1; j <= 13; ++j)
			{
				pk = selectPoker(i, j);
				m_pParent->addChild(pk);
				m_arrPokers->addObject(pk);
				pk->setVisible(false);
			}
		}
		isRet = true;
	} while (0);
	return isRet;
}


NiuPoker* PorkerManager::selectPoker(int huaSe, int num)
{
	NiuPoker* pk;
	char path[256] = { 0 };
	sprintf(path, "pokerBig/%d_%d@2x.png", huaSe, num);
	pk = NiuPoker::create("poker.png", cocos2d::Rect(0, 0, pkWidth_small, pkHeight_small));
	pk->setHuaSe(huaSe);
	pk->setNum(num);
	pk->setGameMain(dynamic_cast<GamePlayScene*>(m_pParent));
	return pk;
}

void PorkerManager::SendPorker(const vector<S_PlayerPorker>& porkers)
{
	for (int kk = 0; kk < 5; ++kk)
	{
		for (int i = 0; i < porkers.size(); ++i)
		{
			for (int j = 0; j < m_pSitManager->m_inRoomPlayerID.size(); ++j)
			{
				if (porkers[i].playerID == m_pSitManager->m_inRoomPlayerID[j])
				{
					MovePk(m_pSitManager->m_inRoomPlayer[j], (NiuPoker*)m_arrPokers->getObjectAtIndex(porkers[i].vecPorkerIndex[kk]));
					break;
				}
			}
		}
	}		
}