//
//  NiuPoker.cpp
//  BullNiuPoker
//
//  Created by 陈冬梅 on 16/7/25.
//
//

#include "NiuPoker.hpp"
#include "GamePlayScene.h"

NiuPoker::NiuPoker() :m_isSelect(false), m_isDianJi(false){
    
}
NiuPoker::~NiuPoker(){
    
}

NiuPoker* NiuPoker::create(const char *pszFileName, const Rect& rect){
    NiuPoker* pk = new NiuPoker();
    if (pk && pk->initWithFile(pszFileName, rect))
    {
        pk->autorelease();
        return pk;
    }
    CC_SAFE_DELETE(pk);
    return pk;
}

void NiuPoker::showFront(){
    if (m_num<3)
        this->setTextureRect(Rect((10+this->m_num)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
    else
        this->setTextureRect(Rect((this->m_num - 3)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
}
void NiuPoker::showLast(){
    this->setTextureRect(Rect(PaiHaoBM*pkWidth, HuaSeBM*pkHeight, pkWidth, pkHeight));
}

NiuPoker* NiuPoker::copy(){
    NiuPoker* pk;
    if (m_num<3)
        pk = NiuPoker::create("Poker.png", Rect((10+this->m_num)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
    else
        pk = NiuPoker::create("Poker.png", Rect((this->m_num - 3)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
    pk->m_isDianJi = this->m_isDianJi;
    pk->m_isSelect = this->m_isSelect;
    pk->setHuaSe(this->getHuaSe());
    pk->setNum(this->getNum());
    pk->m_gameMain = this->m_gameMain;
    return pk;
}

void NiuPoker::printPoker(){
    switch (this->m_huaSe) {
        case HeiTao:
            log("黑桃 %d",this->m_num);
            break;
        case HongTao:
            log("红桃 %d",this->m_num);
            break;
        case MeiHua:
            log("梅花 %d",this->m_num);
            break;
        case FangKuai:
            log("方片 %d",this->m_num);
            break;
        default:
            break;
    }
}





























