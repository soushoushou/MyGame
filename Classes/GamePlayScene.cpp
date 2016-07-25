#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "constString.h"

USING_NS_CC;

#define TAG_STARTGAME_BTN	1	

GamePlayScene::GamePlayScene() :m_timeLayer(NULL), m_startGameBtn(NULL), m_bReady(false)
{

}

Scene* GamePlayScene::createScene()
{
	auto scene = Scene::create();
	auto gamePlayScene = GamePlayScene::create();
	scene->addChild(gamePlayScene);
	return scene;
}

void GamePlayScene::update(float delta)
{
	Size size = Director::sharedDirector()->getWinSize();
	auto server = DebugSimpleServer::getInstance();
	if (server->isAllReady())
	{
		if (!m_timeLayer && m_bReady)
		{
			m_timeLayer = TimeLayer::create();
			m_timeLayer->setFrameSprite("timeWait.png", Vec2(size.width / 2, size.height / 2 - 20));
			m_timeLayer->setTime(5, 20, Vec2(size.width / 2, size.height / 2 - 20));
			addChild(m_timeLayer);
		}
		if (m_timeLayer && m_timeLayer->canRemove())
		{
			this->removeChild(m_timeLayer);
			this->removeChild(m_startGameBtn);
		}
	}
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
	scheduleUpdate();
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

	m_startGameBtn = Button::create("start.png");
	if (!m_startGameBtn) return false;

	m_startGameBtn->setScale(0.4, 0.4);

	m_startGameBtn->setTag(TAG_STARTGAME_BTN);

	m_startGameBtn->setScale9Enabled(true);

	m_startGameBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 100));

	m_startGameBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));

	this->addChild(m_startGameBtn);

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
			//模拟当所有玩家都准备好后再倒计时
			DebugSimpleServer::getInstance()->playerReady("alw");
			m_bReady = !m_bReady;
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


