#pragma once

#include "cocos2d.h"
#include <utility>
using namespace std;

class LoginScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void loading();
	void onCreateUserResponse(void* responseData);
	CREATE_FUNC(LoginScene);
private:
};

