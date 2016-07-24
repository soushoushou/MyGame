#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "TimeLayer.h"
#include "constString.h"

USING_NS_CC;

#define TAG_STARTGAME_BTN	1	

Scene* GamePlayScene::createScene()
{
	auto scene = Scene::create();
	auto gamePlayScene = GamePlayScene::create();
	scene->addChild(gamePlayScene);
	return scene;
}

//初始化
bool GamePlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (!initBackground()) return false;
	if (!initButtons()) return false;
	return true;
}

//初始化背景
bool GamePlayScene::initBackground()
{
	auto size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	auto spriteBK = Sprite::create("game.jpg");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spriteBK);
	return true;
}

bool GamePlayScene::initButtons()
{
	auto size = Director::getInstance()->getVisibleSize();

	Button* startGameBtn = Button::create("start.png");
	if (!startGameBtn) return false;

	startGameBtn->setScale(0.4, 0.4);

	startGameBtn->setTag(TAG_STARTGAME_BTN);

	startGameBtn->setScale9Enabled(true);

	startGameBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 100));

	startGameBtn->addTouchEventListener(GamePlayScene::onBtnTouch);

	this->addChild(startGameBtn);

	return true;
}

void GamePlayScene::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Size size = Director::sharedDirector()->getWinSize();
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case TAG_STARTGAME_BTN:
		{
			log("start game");
			TimeLayer* timeLayer = TimeLayer::create();
			timeLayer->setFrameSprite("timeWait.png", Vec2(size.width / 2, size.height / 2 - 20));
			timeLayer->setTime(5, 20, Vec2(size.width / 2, size.height / 2 - 20));
			butten->getParent()->addChild(timeLayer);
			break;
		}
		}
	}
}

void GamePlayScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


