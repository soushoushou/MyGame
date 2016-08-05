//
//  NiuPoker.cpp
//  BullNiuPoker
//
//  Created by ³Â¶¬Ã· on 16/7/25.
//
//

#include "NiuPoker.h"
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
    char path[256] = { 0 };
    sprintf(path, "pokerBig/%d_%d@2x.png", m_huaSe,m_num);
    this->setTexture(path);
//	if (m_num<3)
//		this->setTextureRect(Rect((10 + this->m_num)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
//	else
//		this->setTextureRect(Rect((this->m_num - 3)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
}
void NiuPoker::showLast(){
    this->setTexture("pokerBig/card_back@2x.png");
//	this->setTextureRect(Rect(PaiHaoBM*pkWidth, HuaSeBM*pkHeight, pkWidth, pkHeight));
}

void NiuPoker::showFront_small(){
    char path[256] = { 0 };
    if ((m_num==2&&m_huaSe==1)||(m_num==1&&m_huaSe==3)) {
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
//	if (m_num<3)
//		pk = NiuPoker::create("Poker.png", Rect((10 + this->m_num)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
//	else
//		pk = NiuPoker::create("Poker.png", Rect((this->m_num - 3)*pkWidth, this->m_huaSe*pkHeight, pkWidth, pkHeight));
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
		log("ºÚÌÒ %d", this->m_num);
		break;
	case HongTao:
		log("ºìÌÒ %d", this->m_num);
		break;
	case MeiHua:
		log("Ã·»¨ %d", this->m_num);
		break;
	case FangKuai:
		log("·½Æ¬ %d", this->m_num);
		break;
	default:
		break;
	}
}
