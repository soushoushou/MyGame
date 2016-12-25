#include "MainScene.h"
#include "toolFunctions.h"
#include "constString.h"
#include "ShadeLayer.h"
#include "PopupLayer.h"
#include "GamePlayScene.h"
#include "ShopLayer.h"
#include "Help.h"
#include "LoginScene.h"

using namespace ui;


#define TAG_CREATEROOM_BTN	1	
#define TAG_JOINGAME_BTN	2
#define TAG_SHOP_BTN		3
#define TAG_RANK_BTN		4
#define TAG_FREEDOMFIGHT_BTN	5
#define TAG_NOTICE_BTN		6
#define TAG_SETTING_BTN		7
#define TAG_BACK_BTN		8




MainScene::MainScene(int playerID):
m_playerID(playerID), m_strPlayerName(""), m_currentDiamond(0), m_currentMoney(0)
{
	m_pNoticeLabel = NULL;
	m_pUser = NULL;
}


MainScene::~MainScene()
{
	if (m_pUser)
	{
		delete m_pUser;
		m_pUser = nullptr;
	}
}

Scene* MainScene::scene(int playerID){
	Scene* scene = Scene::create();
	MainScene * mainScene = MainScene::createMainScene(playerID);
	if(mainScene!=nullptr)
	scene->addChild(mainScene);
	return scene;
}

MainScene* MainScene::createMainScene(int playerID)
{
	MainScene *pRet = new(std::nothrow) MainScene(playerID); 
    if (pRet && pRet->init()) 
	{ 
        pRet->autorelease(); 
        return pRet; 
	} 
	else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


//初始化各种
bool MainScene::init()
{
	CCLayer::init();
	scheduleUpdate();
	if (!initBackground()) return false;
	if (!initButtons()) return false;
	if (!initNotice()) return false;
	if (!initPlayerProfile()) return false;


	S_ZZ_GetPlayerInfoReq req(m_playerID);
	NetworkManger::getInstance()->SendRequest(req);

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
		m_pUser = UserProfileUIInMainScene::create(this);
		m_pUser->setProfile(Vec2(30, 17), "MainScene/timo.png", m_strPlayerName, m_currentDiamond, m_currentMoney);
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
	Button* pJoinRoomBtn = Button::create("MainScene/joinRoom-normal.png", "MainScene/joinRoom-pressed.png");
	if (!pJoinRoomBtn) return false;
	Button* pCreateRoomBtn = Button::create("MainScene/createRoom-normal.png", "MainScene/createRoom-pressed.png");
	if (!pCreateRoomBtn) return false;
	Button* pFreedomFightBtn = Button::create("MainScene/freedomFight-normal.png", "MainScene/freedomFight-pressed.png");
	if (!pFreedomFightBtn) return false;
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

	this->addChild(pCreateRoomBtn);
	this->addChild(pJoinRoomBtn);
	this->addChild(pShopBtn);

	this->addChild(pRankBtn);

	this->addChild(pFreedomFightBtn);
	this->addChild(pSettingBtn);
	this->addChild(pBackBtn);
	this->addChild(pNoticeBtn);
	
	pJoinRoomBtn->setTag(TAG_JOINGAME_BTN);
	pCreateRoomBtn->setTag(TAG_CREATEROOM_BTN);
	pFreedomFightBtn->setTag(TAG_FREEDOMFIGHT_BTN);
	pShopBtn->setTag(TAG_SHOP_BTN);
	pRankBtn->setTag(TAG_RANK_BTN);
	pSettingBtn->setTag(TAG_SETTING_BTN);
	pBackBtn->setTag(TAG_BACK_BTN);
	pNoticeBtn->setTag(TAG_NOTICE_BTN);

	pCreateRoomBtn->setScale9Enabled(true);
	pJoinRoomBtn->setScale9Enabled(true);
	pShopBtn->setScale9Enabled(true);
	pFreedomFightBtn->setScale9Enabled(true);
	pNoticeBtn->setScale9Enabled(true);
	pRankBtn->setScale9Enabled(true);
	pSettingBtn->setScale9Enabled(true);
	pBackBtn->setScale9Enabled(true);

	pJoinRoomBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pJoinRoomBtn->getContentSize().width / 2, 348)));
	pCreateRoomBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pCreateRoomBtn->getContentSize().width / 2, 233)));
	pFreedomFightBtn->setPosition(Director::getInstance()->convertToUI(Vec2(765 + pFreedomFightBtn->getContentSize().width / 2, 465)));
	pNoticeBtn->setPosition(Director::getInstance()->convertToUI(Vec2(705 + pNoticeBtn->getContentSize().width / 2, 574 + pNoticeBtn->getContentSize().height / 2)));
	pRankBtn->setPosition(Director::getInstance()->convertToUI(Vec2(840 + pRankBtn->getContentSize().width / 2, 574 + pRankBtn->getContentSize().height / 2)));
	pShopBtn->setPosition(Director::getInstance()->convertToUI(Vec2(1050 + pShopBtn->getContentSize().width / 2, 550 + pShopBtn->getContentSize().height / 2)));
	pSettingBtn->setPosition(Director::getInstance()->convertToUI(Vec2(947+pSettingBtn->getContentSize().width/2 , 22 + pSettingBtn->getContentSize().height / 2)));
	pBackBtn->setPosition(Director::getInstance()->convertToUI(Vec2(1050 + pBackBtn->getContentSize().width / 2, 26 + pBackBtn->getContentSize().height / 2)));

	pCreateRoomBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch,this));
	pJoinRoomBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pShopBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pRankBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pFreedomFightBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pSettingBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pBackBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));
	pNoticeBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onBtnTouch, this));


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

int MainScene::getDiamond() const
{
	return m_currentDiamond;
}

int MainScene::getMoney() const
{
	return m_currentMoney;
}

int MainScene::getPlayerID() const
{
	return m_playerID;
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
			PopupLayer* pl = PopupLayer::createRoomDialog("popuplayer/startgamepopupbg.png", Size(710, 499));
			pl->setCallbackFunc(butten->getParent(), callfuncN_selector(MainScene::buttonCallback));

			butten->getParent()->addChild(pl);
	
			break;
		}
		case TAG_JOINGAME_BTN:
		{
			log("join room!");
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			PopupLayer* pl = PopupLayer::joinRoomWith9Dialog("popuplayer/joinRoomBg2.png", Size(621, 542));
			butten->getParent()->addChild(pl);
			break;
		}
		case TAG_SHOP_BTN:
		{
			log("shop");
			Director::getInstance()->replaceScene(ShopLayer::createScene(m_playerID,m_currentDiamond,m_currentMoney));
			break;
		}

		case TAG_RANK_BTN: {
			S_ZZ_SearchZhanjiReq req(m_playerID);
			NetworkManger::getInstance()->SendRequest(req);
			break; }

		case TAG_NOTICE_BTN:
		{
			log("NOTIC");
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			PopupLayer* pl = PopupLayer::noticeDialog("popuplayer/backbg.png", Size(size.width / 2, size.height / 7 * 4));
			butten->getParent()->addChild(pl);
			break;
		}

		case TAG_SETTING_BTN: {
			log("SETTING");
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			PopupLayer* pl = PopupLayer::settingDialog("popuplayer/settingbg.png", Size(size.width / 2, size.height / 7 * 4));
			butten->getParent()->addChild(pl);
			break; }
		case TAG_BACK_BTN: {
			auto pl = PopupLayer::backDialog("popuplayer/backbg.png", Size(610, 399), "quit room", "Are you sure?");
			butten->getParent()->addChild(pl);
			pl->setCallbackFunc(this, callfuncN_selector(MainScene::buttonCallback));
			break;
			}
		}

	}
}
//帧刷新
void MainScene::update(float delta)
{
	if (!NetworkManger::getInstance()->ackQueueIsEmpty())
	{
		unsigned short cmd = NetworkManger::getInstance()->getQueueFrontACKCmd();			//获得ack的协议号
		log("MainScene::connect suc cmd=%d", cmd);
		switch (cmd)
		{
			case PP_ZZ_DOUNIU_GET_FOLEINFO_ACK:
			{
				S_ZZ_GetPlayerInfoACK ack = S_ZZ_GetPlayerInfoACK::convertDataFromBinaryData(NetworkManger::getInstance()->getQueueFrontACKBinaryData());
				NetworkManger::getInstance()->popACKQueue();
				log("LoginScene::onCreateUserResponse get data!");

				m_strPlayerName = ack.m_strPlayerName;
				m_currentDiamond = ack.m_currentDiamond;

				m_pUser->setProfile(Vec2(30, 17), "MainScene/timo.png", m_strPlayerName, m_currentDiamond, m_currentMoney);
			}
			break;

			case PP_ZZ_DOUNIU_CREATE_ROOM_ACK:
			{
				S_ZZ_CreateRoomACK cr = S_ZZ_CreateRoomACK::convertDataFromBinaryData(NetworkManger::getInstance()->getQueueFrontACKBinaryData());
				NetworkManger::getInstance()->popACKQueue();
				if (cr.m_statusCode == 0)
				{
					Director::getInstance()->replaceScene(GamePlayScene::createScene(m_playerID, cr.m_roomID));
				}
				else
					log("in update but create room failed");

			}
			break;

			case PP_ZZ_DOUNIU_JOIN_ROOM_ACK:
			{
				S_ZZ_JoinRoomACK cr = S_ZZ_JoinRoomACK::convertDataFromBinaryData(NetworkManger::getInstance()->getQueueFrontACKBinaryData());
				NetworkManger::getInstance()->popACKQueue();
				if (cr.m_isOK == 0)
				{
					Director::getInstance()->replaceScene(GamePlayScene::createScene(m_playerID, cr.m_roomID));
				}
				else
				{
					log("in update but join room failed");
				}
			}
			break;

			case PP_ZZ_DOUNIU_QUIT_ROOM_ACK:
			{
				NetworkManger::getInstance()->popACKQueue();
			}
			break;

			case PP_ZZ_DOUNIU_QUERY_ZHANJI_ACK:
			{
				S_ZZ_SearchZhanjiACK s = S_ZZ_SearchZhanjiACK::convertDataFromBinaryData(NetworkManger::getInstance()->getQueueFrontACKBinaryData());
				NetworkManger::getInstance()->popACKQueue();
				PopupLayer* pl = PopupLayer::recordDialog("popuplayer/noticeBg.png", Size(710, 499));
				vector<pair<int, int>> quickMessage;
				for (int i = 0; i < s.m_roomIDs.size(); ++i)
				{
					quickMessage.push_back(pair<int, int>(s.m_roomIDs[i], s.m_scores[i]));
				}
				pl->createListView(quickMessage);
				this->addChild(pl);
			}
			break;
		}
	}
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
	log("button call back. tag: %d", pNode->getTag());
	NetworkManger::getInstance()->shutDownNetwork();
	Director::getInstance()->replaceScene(LoginScene::createScene());
}

