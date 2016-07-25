#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "DebugSimpleServer.h"
#include "TimeLayer.h"

USING_NS_CC;
using namespace ui;

class GamePlayScene : public cocos2d::Layer
{
public:
	GamePlayScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GamePlayScene);

	//virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void update(float delta);
private:
	bool initBackground();
	bool initButtons();
	bool initPlayerProfile();
private:
	TimeLayer* m_timeLayer;
	Button* m_startGameBtn;
	bool m_bReady;
};

#endif // __GAMESCENE_SCENE_H__
