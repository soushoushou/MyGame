#pragma once

#include "cocos2d.h"
class LoginScene : public cocos2d::Layer
{
public:
	//LoginScene();
	//~LoginScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void loading();
	// implement the "static create()" method manually
	CREATE_FUNC(LoginScene);
};

