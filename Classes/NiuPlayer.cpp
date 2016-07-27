//
//  NiuPlayer.cpp
//  BullPoker
//
//  Created by 陈冬梅 on 16/7/25.
//
//

#include "NiuPlayer.hpp"
#include "NiuPoker.hpp"


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
    if (m_iPlayerClass == 0 || m_iPlayerClass == 3 || m_iPlayerClass==6)
    {
        x = size.width / 2 - ((m_arrPk->count() - 1)*pkJianJu + pkWidth) / 2;
        y = m_point.y;
    }
    else if (m_iPlayerClass == 1 || m_iPlayerClass == 4 || m_iPlayerClass == 5)
    {
        x = m_point.x;
        y = m_point.y;
    }
    else if (m_iPlayerClass == 2)
    {
        x = size.width / 2 - (m_arrPk->count()*pkWidth + (m_arrPk->count() - 1)*pkJianJu) / 2;
        y = m_point.y;
    }
    int num = 0;
    Object* object;
    if (m_iPlayerClass != 3 && m_iPlayerClass != 4 && m_iPlayerClass != 5)
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
        if (m_iPlayerClass == 0 || m_iPlayerClass == 3 || m_iPlayerClass == 6)
        {
            pk->showFront();
            pk->setPosition(ccp(x + num*pkJianJu + pkWidth / 2, y));
            if (m_iPlayerClass == 6)
                pk->showLast();
        }
        else if (m_iPlayerClass == 1 || m_iPlayerClass == 4 || m_iPlayerClass == 5)
        {
            pk->showFront();
            if (m_iPlayerClass == 1)
                pk->showLast();
            pk->setPosition(ccp(x, y - num*pkJianJu));
        }
        else if (m_iPlayerClass == 2)
        {
            pk->setPosition(ccp(x + num*pkJianJu + num*pkWidth + pkWidth / 2, y));
        }
        ++num;
    }
    int i = m_arrPk->count() - 1;
    CCARRAY_FOREACH(m_arrPk, object){
        NiuPoker* pk = (NiuPoker*)object;
        if (m_iPlayerClass == 1 || m_iPlayerClass == 4 || m_iPlayerClass == 5)
            pk->setZOrder(size.height - pk->getPositionY());
        if (m_iPlayerClass == 0 || m_iPlayerClass == 3|| m_iPlayerClass == 6)
            pk->setZOrder(pk->getPositionX());
        
    }
}
