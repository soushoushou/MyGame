#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class GamePlayScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GamePlayScene);

	//virtual void onExit();
	static void onBtnTouch(Ref *pSender, Widget::TouchEventType type);

private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();

};

#endif // __GAMESCENE_SCENE_H__
