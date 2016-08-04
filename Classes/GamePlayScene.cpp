#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "constString.h"
#include "Global.h"
#include "NiuPoker.h"
#include "NiuPlayer.h"
USING_NS_CC;

#define TAG_START_BTN	1	

GamePlayScene::GamePlayScene() :m_timeLayer(NULL), m_startGameBtn(NULL), m_bReady(false), m_isSend(true), 
m_iSendPk(0), m_iState(1),m_btnSetting(NULL)

{
	m_player = new NiuPlayer();
	m_playerRight = new NiuPlayer();
	m_playerTopRight = new NiuPlayer();
	m_playerTopLeft = new NiuPlayer();
	m_playerLeft = new NiuPlayer();

	m_arrPokers = __Array::create();
	m_arrPokers->retain();

}

GamePlayScene::~GamePlayScene(){
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_playerRight);
	CC_SAFE_DELETE(m_playerTopRight);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_RELEASE(m_arrPokers);
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
	switch (m_iState)
	{
	case 0:
		//发牌
		SendPk();
		break;
	case 1:
		//倒计时
		if (server->isAllReady())
		{
			if (!m_timeLayer && m_bReady)
			{
				m_timeLayer = TimeLayer::create();
				m_timeLayer->setFrameSprite("game/clock.png", Vec2(size.width / 2, size.height / 2 - 40));
				m_timeLayer->setTime(5, 20, Vec2(size.width / 2, size.height / 2 - 20));
				addChild(m_timeLayer);
			}
			if (m_timeLayer && m_timeLayer->canRemove())
			{
				this->removeChild(m_timeLayer);
				this->removeChild(m_startGameBtn);
				m_iState = 0;
			}
		};
		break;
	default:
		break;
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
	srand((unsigned)time(NULL));//初始化随机种子
	if (!initPlayer()) return false;
	if (!createPokers()) return false;
	if (!xiPai()) return false;
	return true;
}

//初始化背景
bool GamePlayScene::initBackground()
{
	auto size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	auto spriteBK = Sprite::create("game/gamebg.png");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spriteBK);
	return true;
}

bool GamePlayScene::initButtons()
{
	auto size = Director::getInstance()->getVisibleSize();

	m_startGameBtn = Button::create("game/startgame.png");
	if (!m_startGameBtn) return false;

	m_startGameBtn->setTag(TAG_START_BTN);

	m_startGameBtn->setScale9Enabled(true);

	m_startGameBtn->setPosition(Vec2(size.width / 2, size.height / 2 - 150));

	m_startGameBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));

	this->addChild(m_startGameBtn);

	m_btnSetting = new SettingMenuInPlaying(this,Director::getInstance()->convertToUI(Vec2(980 + 68.5, 22)));

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
		case TAG_START_BTN:
		{
			log("start game");
			butten->setEnabled(false);

			//模拟当所有玩家都准备好后再倒计时
			m_bReady = !m_bReady;
			DebugSimpleServer::getInstance()->playerReady("alw");
			break;
		}
		}
	}
}

bool GamePlayScene::initPlayer(){
	Size size = Director::getInstance()->getVisibleSize();
	//设置主玩家的位置
	m_player->setPoint(Vec2(size.width / 2, size.height / 6));
	m_player->setPlayerClass(PlayerType_Me);
	//设置玩家右的位置
	m_playerRight->setPoint(Vec2(size.width - pkWidth * 3, size.height / 2));
	m_playerRight->setPlayerClass(PlayerType_Right);
	//设置玩家上二的位置
	m_playerTopRight->setPoint(Vec2(size.width*0.5 + pkWidth * 3, size.height / 6 * 5));
	m_playerTopRight->setPlayerClass(PlayerType_TopRight);
	//设置玩家上一的位置
	m_playerTopLeft->setPoint(Vec2(size.width*0.5 - pkWidth * 4, size.height / 6 * 5));
	m_playerTopLeft->setPlayerClass(PlayerType_TopLeft);
	//设置玩家左的位置
	m_playerLeft->setPoint(Vec2(65, size.height / 2));
	m_playerLeft->setPlayerClass(PlayerType_Left);
	return true;
}

NiuPoker* GamePlayScene::selectPoker(int huaSe, int num){
	NiuPoker* pk;
	if (num<3) {
		pk = NiuPoker::create("poker.png", Rect((10 + num)*pkWidth, huaSe*pkHeight, pkWidth, pkHeight));
	}
	else{
		pk = NiuPoker::create("poker.png", Rect((num - 3)*pkWidth, huaSe*pkHeight, pkWidth, pkHeight));
	}
	pk->setHuaSe(huaSe);
	pk->setNum(num);
	pk->setGameMain(this);
	return pk;
}

bool GamePlayScene::createPokers(){
	bool isRet = false;
	do
	{
		Size size = Director::getInstance()->getVisibleSize();
		NiuPoker* pk;
		//创建52个牌
		for (int i = 0; i<4; ++i)
		{
			for (int j = 1; j <= 13; ++j)
			{
				pk = selectPoker(i, j);
				pk->setPosition(Vec2(size.width / 2, size.height / 2));
				pk->showLast();
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);

			}
		}
		isRet = true;
	} while (0);
	return isRet;
}
#pragma mark-洗牌
bool GamePlayScene::xiPai(){
	bool isRet = false;
	do
	{
		for (int i = 0; i<52; ++i)
		{
			NiuPoker* pk1 = (NiuPoker*)m_arrPokers->getRandomObject();
			NiuPoker* pk2 = (NiuPoker*)m_arrPokers->getRandomObject();
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		for (int i = 0; i<52; ++i)
		{
			NiuPoker* pk1 = (NiuPoker*)m_arrPokers->getObjectAtIndex(i);
			pk1->printPoker();
		}
		isRet = true;
	} while (0);
	return isRet;
}

void GamePlayScene::SendPk(){
	NiuPoker* pk;
	if (m_iSendPk<25)
	{
		pk = (NiuPoker*)m_arrPokers->getObjectAtIndex(m_iSendPk);
		if (m_iSendPk % 5 == 0)
			MovePk(m_player, pk);
		else if (m_iSendPk % 4 == 1)
			MovePk(m_playerRight, pk);
		else if (m_iSendPk % 4 == 2)
			MovePk(m_playerTopRight, pk);
		else if (m_iSendPk % 4 == 3)
			MovePk(m_playerTopLeft, pk);
		else
			MovePk(m_playerLeft, pk);
		++m_iSendPk;
		//        m_isSend=false;
	}
	else
		m_iState = 1;
}

void GamePlayScene::func(Node* pSender, void* pData){
	NiuPlayer* play = (NiuPlayer*)pData;
	play->updatePkWeiZhi();
	//    m_isSend = true;
}

void GamePlayScene::MovePk(NiuPlayer* play, NiuPoker* pk)
{
	MoveTo* move;
	__CCCallFuncND* func;
	float time = 0.05;
	play->getArrPk()->addObject(pk);
	move = MoveTo::create(time, play->getPoint());
	func = __CCCallFuncND::create(this, callfuncND_selector(GamePlayScene::func), play);
	Sequence* sequence = Sequence::create(move, func, NULL);
	pk->runAction(sequence);
}

void GamePlayScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}


