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

NiuPoker::NiuPoker() :m_isSelect(false), m_isDianJi(false){
    touchListener=EventListenerTouchOneByOne::create();
    touchListener->onTouchEnded=[=](Touch *touch,Event *event){
//        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        m_isDianJi=!m_isDianJi;
        if (m_isDianJi) {
            if (PorkerManager::m_touchPokers.size()==2) {
                PorkerManager::m_touchPokers.pop_back();
                PorkerManager::m_touchPokers[0]->m_isDianJi=false;
            }
            PorkerManager::m_touchPokers.push_back(this);
        }
        else{
            for(int i=0;i<PorkerManager::m_touchPokers.size();i++)
            {
                NiuPoker *pk=PorkerManager::m_touchPokers[i];
                if (pk->m_num==m_num && pk->m_huaSe==m_huaSe) {
                    vector<NiuPoker*>::iterator it = PorkerManager::m_touchPokers.begin()+i;
                    PorkerManager::m_touchPokers.erase(it);
                }
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
NiuPoker::~NiuPoker(){

}

NiuPoker* NiuPoker::create(){
	NiuPoker* pk = new NiuPoker();
	if (pk)
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
	pk->m_isDianJi = this->m_isDianJi;
	pk->m_isSelect = this->m_isSelect;
	pk->setHuaSe(this->getHuaSe());
	pk->setNum(this->getNum());
	pk->m_gameMain = this->m_gameMain;
	return pk;
}

void NiuPoker::setTouchPriority(){
    m_isDianJi=!m_isDianJi;
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
