#include "PorkerManager.h"
#include "GamePlayScene.h"

PorkerManager::PorkerManager(Node* parent, SiteManager* pSite) :m_pParent(parent), m_pSitManager(pSite), m_currentPokerActionIndex(0)
{
	createPokers();
}


PorkerManager::~PorkerManager()
{
	m_arrPokers->release();
}

void PorkerManager::MovePk(NiuPlayer* play, NiuPoker* pk)
{
	MoveTo* move;
	__CCCallFuncND* func;
	float time = 0.25;
	play->getArrPk()->addObject(pk);
	move = MoveTo::create(time, play->getPoint());
	func = __CCCallFuncND::create(m_pParent, callfuncND_selector(PorkerManager::PokerAction::updatePokerPos), play);
	Sequence* sequence = Sequence::create(move, func, NULL);
	sequence->setTag(0);
	sequence->retain();
	m_poker2Actions.push_back(make_pair(pk, sequence));
}

void PorkerManager::PokerAction::updatePokerPos(Node* pSender, void* pData)
{
	NiuPlayer* play = (NiuPlayer*)pData;
	play->updatePkWeiZhi();
}


bool PorkerManager::createPokers()	
{
	m_arrPokers = __Array::create();
	m_arrPokers->retain();
	Size sz = Director::getInstance()->getVisibleSize();
	bool isRet = false;
	do
	{
		NiuPoker* pk;
		//创建52个牌
		for (int i = 1; i <= 13; ++i)
		{
			for (int j = 1; j <= 4; ++j)
			{
				pk = selectPoker(j, i);
				m_pParent->addChild(pk);
				m_arrPokers->addObject(pk);
				pk->showLast();
				pk->setPosition(Vec2(sz.width / 2, sz.height / 2));
				pk->setVisible(true);
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
	//第几张牌
	for (int kk = 0; kk < 5; ++kk)
	{
		//第几个人
		for (int i = 0; i < porkers.size(); ++i)
		{
			//发牌
			for (int j = 0; j < m_pSitManager->m_inRoomPlayerID.size(); ++j)
			{
				if (porkers[i].playerID == m_pSitManager->m_inRoomPlayerID[j])
				{
					MovePk(m_pSitManager->m_inRoomPlayer[j], ((NiuPoker*)m_arrPokers->getObjectAtIndex(porkers[i].vecPorkerIndex[kk])));
					break;
				}
			}
		}
	}
}

bool PorkerManager::RunActions()
{
	if (m_currentPokerActionIndex < m_poker2Actions.size())
	{
		//没跑的动画
		if (m_poker2Actions[m_currentPokerActionIndex].second->getTag() == 0 && 
			m_poker2Actions[m_currentPokerActionIndex].first->getNumberOfRunningActions() == 0)
		{
			m_poker2Actions[m_currentPokerActionIndex].first->runAction(m_poker2Actions[m_currentPokerActionIndex].second);
			m_poker2Actions[m_currentPokerActionIndex].second->setTag(1);
			return false;
		}
		if (!m_poker2Actions[m_currentPokerActionIndex].second->isDone())
		{
			return false;
		}
		else
			++m_currentPokerActionIndex;
	}
	else
	{
		for (int i = 0; i < m_poker2Actions.size(); ++i)
		{
			m_poker2Actions[i].second->setTag(0);
		}
		return true;
	}
	return false;
}

void PorkerManager::ShowAllPorkers()
{
	for (int i = 0; i < m_pSitManager->m_inRoomPlayer.size(); ++i)
	{
		if (m_pSitManager->m_inRoomPlayer[i] != nullptr)
		{
			m_pSitManager->m_inRoomPlayer[i]->showAllPokers();
		}
	}
}

void PorkerManager::EmptyAllPorkers()
{
	int count = 0;
	cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < m_pSitManager->m_inRoomPlayer.size(); ++i)
	{
		if (m_pSitManager->m_inRoomPlayer[i] != nullptr)
		{
			m_pSitManager->m_inRoomPlayer[i]->emptyAllPokers();
			++count;
		}
	}
	for (int i = 0; i < 52; i++) {
		NiuPoker* pk = (NiuPoker*)m_arrPokers->getObjectAtIndex(i);
		pk->setPosition(Vec2(Size.width / 2, Size.height / 2));
		pk->showLast();
		pk->setVisible(true);
	}
	m_currentPokerActionIndex = 0;
	for (int i = 0; i < m_poker2Actions.size(); ++i)
	{
		m_poker2Actions[i].second->release();
	}
	m_poker2Actions.clear();
}