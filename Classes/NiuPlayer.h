//
//  NiuPlayer.hpp
//  BullPoker
//
//  Created by ≥¬∂¨√∑ on 16/7/25.
//
//

//#ifndef NiuPlayer_h
//#define NiuPlayer_h
#pragma once

#include <stdio.h>
#include "cocos2d.h"
//#include "GamePlayScene.h"

USING_NS_CC;

/** ÕÊº“¿‡–Õ */
enum PlayerType
{
	/** ÕÊº“◊‘º∫ */
	PlayerType_Me,
	/** ”“±ﬂÕÊº“ */
	PlayerType_Right,
	/** …œ≤ø”“±ﬂÕÊº“ */
	PlayerType_TopRight,
	/** …œ≤ø◊Û±ﬂÕÊº“ */
	PlayerType_TopLeft,
	/** ◊Û±ﬂÕÊº“ */
	PlayerType_Left
};



class NiuPlayer : public Object
{
public:
	NiuPlayer();
	~NiuPlayer();
	void updatePkWeiZhi();
    void showAllPokers();
    void emptyAllPokers();

private:
	CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);
	CC_SYNTHESIZE(cocos2d::Point, m_point, Point);
	CC_SYNTHESIZE(PlayerType, m_iPlayerClass, PlayerClass);
    Sprite *m_multiImg;
	int m_sendPokerCount;				//发牌动画计数
};
//#endif /* NiuPlayer_h */
