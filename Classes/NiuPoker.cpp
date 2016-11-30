//
//  NiuPoker.cpp
//  BullNiuPoker
//
//  Created by ³Â¶¬Ã· on 16/7/25.
//
//

#include "NiuPoker.h"
#include "GamePlayScene.h"
#include "PorkerManager.h"

NiuPoker::NiuPoker() :m_isSelect(false), m_isTouchable(false)
{
}
NiuPoker::~NiuPoker(){

}

void NiuPoker::setTouchable(bool isTouchable /* = true */)
{
	m_isTouchable = isTouchable;
}

NiuPoker* NiuPoker::create(){
	NiuPoker* pk = new NiuPoker();
	if (pk && pk->init())
	{
		pk->autorelease();
		return pk;
	}
	CC_SAFE_DELETE(pk);
	return pk;
}

void NiuPoker::showFront(){
    char path[256] = { 0 };
    sprintf(path, "pokerBig/%d_%d@2x.png", m_huaSe,m_num);
    this->setTexture(path);
}
void NiuPoker::showLast(){
    this->setTexture("pokerBig/card_back@2x.png");
}

void NiuPoker::showFront_small(){
    char path[256] = { 0 };
    if ((m_num==2&&m_huaSe==1)||(m_num==1&&m_huaSe==3)||m_num>=11) {
        sprintf(path, "pokerSmall/%d-20_%d.png", m_huaSe,m_num);
    }else{
        sprintf(path, "pokerSmall/%d-20_%d.jpg", m_huaSe,m_num);
    }
    
    this->setTexture(path);
}

void NiuPoker::showLast_small(){
    this->setTexture("pokerSmall/card_back.png");
}

NiuPoker* NiuPoker::copy(){
	NiuPoker* pk;
	pk->m_isSelect = this->m_isSelect;
	pk->m_isTouchable = this->m_isTouchable;
	pk->setHuaSe(this->getHuaSe());
	pk->setNum(this->getNum());
	pk->m_gameMain = this->m_gameMain;
	return pk;
}

bool NiuPoker::upOrDownPoker(int& up)
{
	if (!m_isTouchable)
	{
		return false;
	}
	m_isSelect = !m_isSelect;
	if (m_isSelect)
	{
		this->setPositionY(this->getPositionY() + 30);
	}
	else
		this->setPositionY(this->getPositionY() - 30);
	return m_isTouchable;
}


void NiuPoker::printPoker(){
	switch (this->m_huaSe) {
	case HeiTao:
		log("heitao %d", this->m_num);
		break;
	case HongTao:
		log("hongtao %d", this->m_num);
		break;
	case MeiHua:
		log("meihua %d", this->m_num);
		break;
	case FangKuai:
		log("fangkuai %d", this->m_num);
		break;
	case Gui:
		log("gui %d", this->m_num);
		break;
	default:
		log("other");
		break;
	}
}
