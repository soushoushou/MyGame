#include "MainScene.h"
#include "toolFunctions.h"

#define TAG_CREATEROOM_BTN	1	
#define TAG_JOINROOM_BTN	2
#define TAG_SHOP_BTN		3
#define TAG_RANK_BTN		4
#define TAG_ROLE_BTN		5
#define TAG_CASH_BTN		6
#define TAG_DIAMOND_BTN		7



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
	scene->addChild(mainScene);
	return scene;
}

//≥ı ºªØ≥°æ∞
bool MainScene::init()
{
	CCLayer::init();
	scheduleUpdate();
	if (!initBackground()) return false;
	if (!initButtons()) return false;
	if (!initNotice()) return false;
	if (!initPlayerProfile()) return false;

	return true;
}

//≥ı ºªØ±≥æ∞
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

//��ʼ�������Ϣ�����ǳƣ��ȼ���ͷ���
bool MainScene::initPlayerProfile()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (!m_pUser)
	{
		m_pUser = new User(50, size.height - 60, ASCII2UTF_8("�ǳ�:asdfds"), ASCII2UTF_8("Lv:14"));
		this->addChild(m_pUser->getHeadSprite());
		this->addChild(m_pUser->getLevel());
		this->addChild(m_pUser->getPlayerName());
	}
	return true;
}


bool MainScene::initNotice()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_pNoticeLabel = LabelTTF::create("抵制不良游戏，拒绝盗版游戏。 注意自我保护，谨防受骗上当。 适度游戏益脑，沉迷游戏伤身。 合理安排时间，享受健康生活。", "Arial", 25);
if (!m_pNoticeLabel) return false;
	m_pNoticeLabel->setPosition(Vec2(size.width + m_pNoticeLabel->getContentSize().width / 2, 50));
	m_pNoticeLabel->setColor(Color3B(255, 0, 0));
	this->addChild(m_pNoticeLabel);
	return true;
}

//≥ı ºªØ∏˜÷÷∞¥≈•
bool MainScene::initButtons()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	Button* pCreateRoomBtn = Button::create("createRoom_normal.png");
	if (!pCreateRoomBtn) return false;
	Button* pJoinRoomBtn = Button::create("joinRoom_normal.png");
	if (!pJoinRoomBtn) return false;
	Button* pShopBtn = Button::create("shop_normal.png");
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
	pCreateRoomBtn->setScale(0.8, 0.8);
	pJoinRoomBtn->setScale(0.8, 0.8);
	pShopBtn->setScale(0.8, 0.8);

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
	pCashBtn->setPosition(Vec2(280, size.height-50));
	pDiamondBtn->setPosition(Vec2(440,size.height-50));
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

void MainScene::flushNoticeLabel(float delta)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float ratio = delta * 60;
	float newX = m_pNoticeLabel->getPositionX() - ratio;
	if (newX < -m_pNoticeLabel->getContentSize().width/2)
	{
		newX = size.width + m_pNoticeLabel->getContentSize().width / 2;
	}
	m_pNoticeLabel->setPositionX(newX);
}

//∞¥≈•µ„ª˜ ¬º˛ªÿµ˜
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

//÷°À¢–¬
void MainScene::update(float delta)
{
	flushNoticeLabel(delta);
}

//Ω¯»Î≥°æ∞
void MainScene::onEnter()
{
	Layer::onEnter();
}


//Õ∆≥ˆ≥°æ∞
void MainScene::onExit()
{
	Layer::onExit();
}
