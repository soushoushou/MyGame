//
//  NiuPoker.hpp
//  BullPoker
//
//  Created by 陈冬梅 on 16/7/25.
//
//

#ifndef NiuPoker_h
#define NiuPoker_h

#include "Global.h"
#include "cocos2d.h"
class GamePlayScene;
USING_NS_CC;
class  NiuPoker : public Sprite
{
public:
	NiuPoker();
	~NiuPoker();
	static NiuPoker* create();
	void showFront();//显示前面
	void showLast();//显示背面
    void showFront_small();
    void showLast_small();
	NiuPoker* copy();
	/** 打印扑克牌 */
	void printPoker();
	void setTouchPriority();
	bool upOrDownPoker(int& up);
	void setTouchable(bool isTouchable = true);
private:
	CC_SYNTHESIZE(bool, m_isSelect, Select);
	CC_SYNTHESIZE(GamePlayScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(int, m_huaSe, HuaSe);
	CC_SYNTHESIZE(int, m_num, Num);
	bool m_isTouchable;
};


#endif /* NiuPoker_h */
