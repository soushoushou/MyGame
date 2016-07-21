#include "MainScene.h"

#define TAG_CREATEROOM_BTN	1	
#define TAG_JOINROOM_BTN	2
#define TAG_SHOP_BTN		3
#define TAG_RANK_BTN		4
#define TAG_ROLE_BTN		5
#define TAG_CASH_BTN		6
#define TAG_DIAMOND_BTN		7


MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

Scene* MainScene::scene(){
	Scene* scene = Scene::create();
	MainScene * mainScene = MainScene::create();
	scene->addChild(mainScene);
	return scene;
}

//初始化场景
bool MainScene::init()
{
	CCLayer::init();
	if (!initBackground()) return false;
	if (!initButtons()) return false;
	return true;
}

bool MainScene::initBackground()
{
	CCSprite* bk = CCSprite::create("mainSceneBG.jpg");
	if (!bk)
	{
		return false;
	}
	this->addChild(bk, 0);
	bk->setAnchorPoint(ccp(0, 0));
	return true;
}

bool MainScene::initButtons()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	Button* pCreateRoomBtn = Button::create("createRoom_normal.png", "createRoom_press.png");
	if (!pCreateRoomBtn) return false;
	Button* pJoinRoomBtn = Button::create("joinRoom_normal.png", "joinRoom_press.png");
	if (!pJoinRoomBtn) return false;
	Button* pShopBtn = Button::create("shop_normal.png", "shop_press.png");
	if (!pShopBtn) return false;
	Button* pCashBtn = Button::create("Cash.png");
	if (!pCashBtn) return false;
	Button* pDiamondBtn = Button::create("Gems.png");
	if (!pDiamondBtn) return false;
	Button* pRoleHelpBtn = Button::create("role.png");
	if (!pRoleHelpBtn) return false;
	Button* pRankBtn = Button::create("rank.png");
	if (!pRankBtn) return false;

	pCashBtn->setScale(0.6, 0.6);
	pDiamondBtn->setScale(0.6, 0.6);
	pRankBtn->setScale(0.7, 0.7);
	pRoleHelpBtn->setScale(0.7, 0.7);

	pCreateRoomBtn->setTag(TAG_CREATEROOM_BTN);
	pJoinRoomBtn->setTag(TAG_JOINROOM_BTN);
	pShopBtn->setTag(TAG_SHOP_BTN);
	pRankBtn->setTag(TAG_RANK_BTN);
	pRoleHelpBtn->setTag(TAG_ROLE_BTN);
	pCashBtn->setTag(TAG_CASH_BTN);
	pDiamondBtn->setTag(TAG_DIAMOND_BTN);

	pCreateRoomBtn->setScale9Enabled(true);
	pJoinRoomBtn->setScale9Enabled(true);
	pShopBtn->setScale9Enabled(true);
	pDiamondBtn->setScale9Enabled(true);
	pCreateRoomBtn->setPosition(Vec2(size.width / 2 + 250, 5 * (size.height / 6)-100));
	pJoinRoomBtn->setPosition(Vec2(size.width / 2 + 250, 3 * (size.height / 6)));
	pShopBtn->setPosition(Vec2(size.width / 2 + 250, size.height / 6+100));
	pCashBtn->setPosition(Vec2(100, size.height-50));
	pDiamondBtn->setPosition(Vec2(260,size.height-50));
	pRoleHelpBtn->setPosition(Vec2(size.width - 150, size.height - 50));
	pRankBtn->setPosition(Vec2(size.width - 75, size.height - 50));

	pCreateRoomBtn->addTouchEventListener(MainScene::onBtnTouch);
	pJoinRoomBtn->addTouchEventListener(MainScene::onBtnTouch);
	pShopBtn->addTouchEventListener(MainScene::onBtnTouch);
	pRankBtn->addTouchEventListener(MainScene::onBtnTouch);
	pRoleHelpBtn->addTouchEventListener(MainScene::onBtnTouch);
	pCashBtn->addTouchEventListener(MainScene::onBtnTouch);
	pDiamondBtn->addTouchEventListener(MainScene::onBtnTouch);


	this->addChild(pCreateRoomBtn);
	this->addChild(pJoinRoomBtn);
	this->addChild(pShopBtn);
	this->addChild(pCashBtn);
	this->addChild(pDiamondBtn);
	this->addChild(pRankBtn);
	this->addChild(pRoleHelpBtn);
	return true;
}


void MainScene::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case TAG_CREATEROOM_BTN:
			log("create room");
			break;
		case TAG_JOINROOM_BTN:
			log("join room");
			break;
		case TAG_SHOP_BTN:
			log("shop");
			break;
		case TAG_RANK_BTN:
			log("rank");
			break;
		case TAG_ROLE_BTN:
			log("role");
			break;
		case TAG_CASH_BTN:
			log("cash");
			break;
		case TAG_DIAMOND_BTN:
			log("diamond");
			break;
		}
	}

}

//进入场景
void MainScene::onEnter()
{
	Layer::onEnter();
}


//推出场景
void MainScene::onExit()
{
	Layer::onExit();
}
