//
//  NiuPlayer.cpp
//  BullPoker
//
//  Created by ³Â¶¬Ã· on 16/7/25.
//
//

#include "NiuPlayer.h"
#include "NiuPoker.h"


NiuPlayer::NiuPlayer()
{
	m_arrPk = __Array::create();
	m_arrPk->retain();
}

NiuPlayer::~NiuPlayer()
{
	CC_SAFE_RELEASE(m_arrPk);
}
void NiuPlayer::updatePkWeiZhi(){
	Size size = Director::getInstance()->getVisibleSize();
	int x, y;
	if (m_iPlayerClass == PlayerType_Me)
	{
		x = size.width / 2 - ((m_arrPk->count() - 1)*(pkWidth_Big+pkJianJu) + pkWidth_Big) / 2;
		y = m_point.y;
	}
	else
	{
		x = m_point.x;
		y = m_point.y;
	}

	int num = 0;
	Ref* object;
	for (int i = 0; m_arrPk->count() != 0 && i<m_arrPk->count() - 1; ++i)
	{
		for (int j = 0; j<m_arrPk->count() - 1 - i; ++j)
		{
			NiuPoker* pk1 = (NiuPoker*)m_arrPk->getObjectAtIndex(j);
			NiuPoker* pk2 = (NiuPoker*)m_arrPk->getObjectAtIndex(j + 1);
			if (pk1->getNum() < pk2->getNum())
				m_arrPk->exchangeObject(pk1, pk2);
		}
	}
	CCARRAY_FOREACH(m_arrPk, object){
		NiuPoker* pk = (NiuPoker*)object;
		
		if (m_iPlayerClass == PlayerType_Me)
		{
            if(num==m_arrPk->count()-1)
                pk->showLast();
            else
                pk->showFront();
            pk->setPosition(Vec2(x + num*(pkWidth_Big+pkJianJu) + pkWidth_Big / 2, y));
            pk->setContentSize(Size(pkWidth_Big, pkHeight_Big));
		}
		else
		{
			pk->showLast_small();
            pk->setPosition(Vec2(x + num*pkWidth_Big*0.3 + pkWidth_Big*0.5, y));
            pk->setContentSize(Size(pkWidth_small, pkHeight_small));
		}
		++num;
	}
	CCARRAY_FOREACH(m_arrPk, object){
		NiuPoker* pk = (NiuPoker*)object;
		pk->setLocalZOrder(pk->getPositionX());

	}
}

void NiuPlayer::showAllPokers(){
    for (int i=0; i< m_arrPk->count(); i++) {
        NiuPoker* pk = (NiuPoker*)m_arrPk->getObjectAtIndex(i);
        if (m_iPlayerClass == PlayerType_Me)
            pk->showFront();
        else
            pk->showFront_small();
    }
}

void NiuPlayer::emptyAllPokers(){
    Size size = Director::getInstance()->getVisibleSize();
    for (int i=0; i<m_arrPk->count(); i++) {
        NiuPoker* pk = (NiuPoker*)m_arrPk->getObjectAtIndex(i);
        pk->setPosition(Vec2(size.width*0.5, size.height*0.5));
        pk->setVisible(false);
    }
    m_arrPk->removeAllObjects();
}
