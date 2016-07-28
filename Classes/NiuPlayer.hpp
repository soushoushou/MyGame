//
//  NiuPlayer.hpp
//  BullPoker
//
//  Created by 陈冬梅 on 16/7/25.
//
//

#ifndef NiuPlayer_hpp
#define NiuPlayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GamePlayScene.h"

USING_NS_CC;

/** 玩家类型 */
enum PlayerType
{
    /** 玩家自己 */
    PlayerType_Me,
    /** 右边玩家 */
    PlayerType_Right,
    /** 上部右边玩家 */
    PlayerType_TopRight,
    /** 上部左边玩家 */
    PlayerType_TopLeft,
    /** 左边玩家 */
    PlayerType_Left
};

class NiuPlayer : public Object
{
public:
    NiuPlayer();
    ~NiuPlayer();
    void updatePkWeiZhi();
    
private:
    CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);
    CC_SYNTHESIZE(Point, m_point, Point);
    CC_SYNTHESIZE(PlayerType, m_iPlayerClass, PlayerClass);
};
#endif /* NiuPlayer_hpp */
