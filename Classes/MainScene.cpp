#include "MainScene.h"
#include "toolFunctions.h"
#include "constString.h"
#include "ShadeLayer.h"
#include "PopupLayer.h"
#include "GamePlayScene.h"
#include "ShopLayer.h"

using namespace ui;


#define TAG_CREATEROOM_BTN	1	
#define TAG_JOINGAME_BTN	2
#define TAG_SHOP_BTN		3
#define TAG_RANK_BTN		4
#define TAG_GAMEHALL_BTN	5
#define TAG_NOTICE_BTN		6
#define TAG_SETTING_BTN		7
#define TAG_BACK_BTN		8




MainScene::MainScene()
{
	m_pNoticeLabel = NULL;
	m_pUser = NULL;
}


MainScene::~MainScene()
{
}

Scene* MainScene::scene(){
	Scene* scene = Scene::create();
	MainScene * mainScene = MainScene::create();
	if(mainScene!=nullptr)
	scene->addChild(mainScene);
	return scene;
}

//初始化各种
bool MainScene::init()
{
	printf("s");
	CCLayer::init();
	printf("s");
	scheduleUpdate();
	printf("s");
	if (!initBackground()) return false;
	if (!initButtons()) return false;
	if (!initNotice()) return false;
	if (!initPlayerProfile()) return false;

	return true;
}

//初始化背景
bool MainScene::initBackground()
{
	CCSprite* bk = CCSprite::create("MainScene/bg.png");
	if (!bk)
	{
		return false;
	}
	this->addChild(bk, 0);
	bk->setAnchorPoint(ccp(0, 0));
	return true;
}

//初始化玩家信息，如昵称，等级，头像等
bool MainScene::initPlayerProfile()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (!m_pUser)
	{
		m_pUser = new UserProfileUIInMainScene(this, Vec2(30,17), "MainScene/timo.png", "LOVEVVV666", 13300,13333);
	}
	return true;
}


bool MainScene::initNotice()
{
	Size size = Director::sharedDirector()->getWinSize();
	m_spRoundRectInNotice = Sprite::create("MainScene/roundRect2.png");
	m_spRoundRectInNotice->setPosition(Vec2(size.width/2,3*size.height/4));
	this->addChild(m_spRoundRectInNotice);
	Sprite *spLaBa = Sprite::create("MainScene/laba.png");
	spLaBa->setPosition(Vec2(size.width / 12, 3 * size.height / 4));
	this->addChild(spLaBa);
	ClippingNode* clipNode = ClippingNode::create();
	clipNode->setContentSize(Size(m_spRoundRectInNotice->getContentSize().width-130,m_spRoundRectInNotice->getContentSize().height));
	auto stencil = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(clipNode->getContentSize().width, 0);
	rectangle[2] = Vec2(clipNode->getContentSize().width, clipNode->getContentSize().height);
	rectangle[3] = Vec2(0, clipNode->getContentSize().height);

	Color4F white(1, 1, 1, 1);
	stencil->drawPolygon(rectangle, 4, white, 1, white);
	clipNode->setStencil(stencil);

	clipNode->setAnchorPoint(Vec2(0.5,0.5));
	clipNode->setPosition(Vec2(size.width / 2+60, 3 * size.height / 4-10));
	this->addChild(clipNode);
	m_pNoticeLabel = LabelTTF::create(g_strMainSceneNotice.c_str(), "Arial", 25);
	if (!m_pNoticeLabel) return false;
	m_pNoticeLabel->setPosition(Vec2(-(clipNode->getContentSize().width / 2+m_pNoticeLabel->getContentSize().width/2), 3 * clipNode->getContentSize().height / 4));
	m_pNoticeLabel->setColor(Color3B(255, 255, 255));
	clipNode->addChild(m_pNoticeLabel);
	return true;
}

//初始化各种按钮
bool MainScene::initButtons()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	Button* pGameHallBtn = Button::create("MainScene/gameHall-normal.png", "MainScene/gameHall-pressed.png");
	if (!pGameHallBtn) return false;
	Button* pCreateRoomBtn = Button::create("MainScene/createRoom-normal.png", "MainScene/createRoom-pressed.png");
	if (!pCreateRoomBtn) return false;
	Button* pJoinGameBtn = Button::create("MainScene/joinGame-normal.png", "MainScene/joinGame-pressed.png");
	if (!pJoinGameBtn) return false;
	Button* pSettingBtn = Button::create("MainScene/setting-normal.png", "MainScene/setting-pressed.png");
	if (!pSettingBtn) return false;
	Button* pBackBtn = Button::create("MainScene/back-normal.png", "MainScene/back-pressed.png");
	if (!pSettingBtn) return false;
	Button* pNoticeBtn = Button::create("MainScene/notice-normal.png", "MainScene/notice-pressed.png");
	if (!pNoticeBtn) return false;
	Button* pRankBtn = Button::create("MainScene/rank-normal.png", "MainScene/rank-pressed.png");
	if (!pRankBtn) return false;
	Button* pShopBtn = Button::create("MainScene/shop-normal.png", "MainScene/shop-pressed.png");
	if (!pShopBtn) return false;

	
	pGameHallBtn->setTag(TAG_GAMEHALL_BTN);
	pCreateRoomBtn->setTag(TAG_CREATEROOM_BTN);
	pJoinGameBtn->setTag(TAG_JOINGAME_BTN);
	pShopBtn->setTag(TAG_SHOP_BTN);
	pRankBtn->setTag(TAG_RANK_BTN);
	pSettingBtn->setTag(TAG_SETTING_BTN);
	pBackBtn->setTag(TAG_BACK_BTN);
	pNoticeBtn->setTag(TAG_NOTICE_BTN);

	pCreateRoomBtn->setScale9Enabled(true);
	pJoinGameBtn->setScale9Enabled(true);
	pShopBtn->setScale9Enabled(true);
	pGameHallBtn->setScale9Enabled(true);
	pNoticeBtn->setScale9Enabled(true);
	pRankBtn->setScale9Enabled(true);
	pSettingBtn->setScale9Enabled(true);
	pBackBtn->setScale9Enabled(true);

	pGameHallBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pGameHallBtn->getContentSize().width / 2, 233)));
	pCreateRoomBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pCreateRoomBtn->getContentSize().width / 2, 348)));
	pJoinGameBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pJoinGameBtn->getContentSize().width / 2, 465)));
	pNoticeBtn->setPosition(Director::getInstance()->convertToUI(Vec2(705 + pNoticeBtn->getContentSize().width / 2, 574 + pNoticeBtn->getContentSize().height / 2)));
	pRankBtn->setPosition(Director::getInstance()->convertToUI(Vec2(840 + pRankBtn->getContentSize().width / 2, 574 + pRankBtn->getContentSize().height / 2)));
	pShopBtn->setPosition(Director::getInstance()->convertToUI(Vec2(1050 + pShopBtn->getContentSize().width / 2, 550 + pShopBtn->getContentSize().height / 2)));
	pSettingBtn->setPosition(Director::getInstance()->convertToUI(Vec2(947+pSettingBtn->getContentSize().width/2 , 22 + pSettingBtn->getContentSize().height / 2)));
	pBackBtn->setPosition(Director::getInstance()->convertToUI(Vec2(1050 + pBackBtn->getContentSize().width / 2, 26 + pBackBtn->getContentSize().height / 2)));

	pCreateRoomBtn->addTouchEventListener(MainScene::onBtnTouch);
	pGameHallBtn->addTouchEventListener(MainScene::onBtnTouch);
	pShopBtn->addTouchEventListener(MainScene::onBtnTouch);
	pRankBtn->addTouchEventListener(MainScene::onBtnTouch);
	pJoinGameBtn->addTouchEventListener(MainScene::onBtnTouch);
	pSettingBtn->addTouchEventListener(MainScene::onBtnTouch);
	pBackBtn->addTouchEventListener(MainScene::onBtnTouch);
	pNoticeBtn->addTouchEventListener(MainScene::onBtnTouch);

	this->addChild(pCreateRoomBtn);
	this->addChild(pGameHallBtn);
	this->addChild(pShopBtn);

	this->addChild(pRankBtn);

	this->addChild(pJoinGameBtn);
	this->addChild(pSettingBtn);
	this->addChild(pBackBtn);
	this->addChild(pNoticeBtn);
	return true;
}

//刷新公告
void MainScene::flushNoticeLabel(float delta)
{
	if (!m_pNoticeLabel)
	{
		return;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float ratio = delta * 60;
	float newX = m_pNoticeLabel->getPositionX() - ratio;

	if (newX < -m_pNoticeLabel->getContentSize().width / 2)
	{
		newX = size.width + m_pNoticeLabel->getContentSize().width / 2;
	}
	m_pNoticeLabel->setPositionX(newX);
}

//触摸监听
void MainScene::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Size size = Director::sharedDirector()->getWinSize();
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case TAG_CREATEROOM_BTN:
		{
			log("create room");
			ShadeLayer* l = ShadeLayer::create();
			l->setFrameSprite("shadeFrame.png", Vec2(size.width / 2, size.height / 2));
			l->setTitle(g_strMessageBosTitle1, "Arial", 10, Vec2(size.width / 2, size.height / 2 + 20));
			l->setContent(g_strHoldOn1, "Arial", 10, Vec2(size.width / 2, size.height / 2 - 20));
			butten->getParent()->addChild(l);
			break;
		}
		case TAG_JOINGAME_BTN:
		{
			Director::getInstance()->replaceScene(GamePlayScene::createScene());
			break;
		}
		case TAG_SHOP_BTN: 
		{
			log("shop");
			Director::getInstance()->replaceScene(ShopLayer::createScene());
			break; 
		}
		case TAG_RANK_BTN:
			log("RANK");
			break;

		case TAG_NOTICE_BTN:
			log("NOTIC");
			break;

		case TAG_GAMEHALL_BTN:
			log("GAMEHALL");
			break;

		case TAG_SETTING_BTN:
			log("SETTING");
			break;
		case TAG_BACK_BTN:
			log("BACK");
			break;
		}
	}

}

//帧刷新
void MainScene::update(float delta)
{
	flushNoticeLabel(delta);
}

//进入场景时
void MainScene::onEnter()
{
	Layer::onEnter();
}


//推出场景时
void MainScene::onExit()
{
	Layer::onExit();
}

void MainScene::buttonCallback(cocos2d::CCNode *pNode) {
	//CCLog("button call back. tag: %d", pNode->getTag());
}
