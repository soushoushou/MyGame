#pragma once

#include "cocos2d.h"
#include "GameSocket.h"

class LoginScene : public cocos2d::Layer
{
public:
	//LoginScene();
	//~LoginScene();
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void loading();
	// implement the "static create()" method manually
	CREATE_FUNC(LoginScene);
private:
	CGameSocket* m_pSocket;
};

