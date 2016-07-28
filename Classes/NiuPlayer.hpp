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
class NiuPlayer : public Object
{
public:
    NiuPlayer();
    ~NiuPlayer();
    void updatePkWeiZhi();
    
private:
    CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);
    CC_SYNTHESIZE(Point, m_point, Point);
    CC_SYNTHESIZE(int, m_iPlayerClass, PlayerClass);
};
#endif /* NiuPlayer_hpp */
