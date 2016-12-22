#include "ShopLayer.h"
#include "toolFunctions.h"
#include "MainScene.h"
#include "UserProfileUI.h"
#include "NetworkManger.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace ui;

#define TAG_BACK_BIN			0		//返回
#define TAG_DIAMOND01_BIN		6		//钻石购买按钮1
#define TAG_DIAMOND02_BIN		30		//钻石购买按钮2
#define TAG_DIAMOND03_BIN		60		//钻石购买按钮3
#define TAG_DIAMOND04_BIN		108		//钻石购买按钮4
#define TAG_DIAMOND05_BIN		208		//钻石购买按钮5
#define TAG_DIAMOND06_BIN		618		//钻石购买按钮6

#define TAG_COIN01_BIN			50		//金币购买按钮1
#define TAG_COIN02_BIN			100		//金币购买按钮2
#define TAG_COIN03_BIN			500		//金币购买按钮3
#define TAG_COIN04_BIN			1000	//金币购买按钮4
#define TAG_COIN05_BIN			2000	//金币购买按钮5
#define TAG_COIN06_BIN			5000	//金币购买按钮6



ShopLayer::ShopLayer(unsigned long long playerID, int diamond, int money, int number) :m_playerID(playerID), m_number(number)
, m_diamond(diamond), m_money(money)
{
}


ShopLayer::~ShopLayer()
{
}

ShopLayer* ShopLayer::create(unsigned long long playerID, int diamond, int money, int number)
{
	ShopLayer *pRet = new(std::nothrow)ShopLayer(playerID, diamond, money, number);
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

Scene* ShopLayer::createScene(unsigned long long playerID, int diamond, int money, int number)
{
	auto scene = Scene::create();
	auto shopLayer = ShopLayer::create(playerID, diamond, money, number);
	scene->addChild(shopLayer);
	return scene;
}

void ShopLayer::update(float delta)
{
	if (!NetworkManger::getInstance()->ackQueueIsEmpty())
	{
		unsigned short cmd = NetworkManger::getInstance()->getQueueFrontACKCmd();			//获得ack的协议号
		log("LoginScene::connect suc cmd=%d", cmd);
		if (cmd == PP_DOUNIU_CHONGZHI_ACK)
		{
			S_BuyDiamondACK ack = S_BuyDiamondACK::convertDataFromBinaryData(NetworkManger::getInstance()->getQueueFrontACKBinaryData());
			NetworkManger::getInstance()->popACKQueue();

			if (ack.m_isOK == 0)
			{
				char buf[100] = { 0 };
				sprintf(buf, "%d", ack.m_currentNum);
				switch (ack.m_buyType)
				{
				case 0:
					m_lblDiamond->setString(buf);
					break;
				case 1:
					m_lblCoin->setString(buf);
					break;
				}
			}

			
		}
	}
}

//初始化基本场景
bool ShopLayer::init()
{
	CCLayer::init();
	scheduleUpdate();
	if (!initBackground()) return false;
	if (!initMenuBar()) return false;
	if (!initTopMenuBar()) return false;
	if (!initButtons()) return false;
	if (!initShow()) return false;
	if (!initDiamondLayer()) return false;
	if (!initCoinLayer()) return false;

	this->addChild(layerCoin);
	this->addChild(layerDiamond);
	//创建一个左边LayerMultiplex
	//layers = LayerMultiplex::create(layerDiamond, layerCoin, nullptr);
	//this->addChild(layers, 0, "layers");
	if (m_number == 0)
	{
		layerDiamond->setVisible(false);
		layerCoin->setVisible(true);
		buyDiamond->setColor(ccColor3B(colBegan.r * 0.60, colBegan.g * 0.60, colBegan.b * 0.60));
		buyCoin->setColor(ccColor3B(colBegan.r, colBegan.g, colBegan.b));
	}
	else
	{
		layerCoin->setVisible(false);
		layerDiamond->setVisible(true);
		buyDiamond->setColor(ccColor3B(colBegan.r, colBegan.g, colBegan.b));
		buyCoin->setColor(ccColor3B(colBegan.r * 0.60, colBegan.g * 0.60, colBegan.b * 0.60));
	}

	scheduleUpdate();
	//onEnter();
	return true;
}

//初始化背景
bool ShopLayer::initBackground()
{
	CCSprite* bk = CCSprite::create("shop/shopbg.png");
	if (!bk)
	{
		return false;
	}
	this->addChild(bk, 0);
	bk->setAnchorPoint(ccp(0, 0));
	return true;
}

//左侧钻石、金币导航条初始化
bool ShopLayer::initMenuBar(){
	layerDiamond = Layer::create();

	//创建2个MenuItemSprite
	buyDiamond = MenuItemSprite::create(Sprite::create("shop/buyDiamond-normal.png"), Sprite::create("shop/buyDiamond-pressed.png"), CC_CALLBACK_1(ShopLayer::tapBarMenuPressed, this));
	buyDiamond->setTag(0);
	buyCoin = MenuItemSprite::create(Sprite::create("shop/buyCoin-normal.png"), Sprite::create("shop/buyCoin-pressed.png"), CC_CALLBACK_1(ShopLayer::tapBarMenuPressed, this));
	buyCoin->setTag(1);

	//获取左侧需要变的颜色
	colBegan = buyDiamond->getColor();
	
	tabBarItems = Menu::create(buyDiamond, buyCoin, NULL);
	tabBarItems->alignItemsVerticallyWithPadding(30);
	tabBarItems->setPosition(Director::getInstance()->convertToUI(Vec2(140, tabBarItems->getContentSize().height / 2 + 35)));
	this->addChild(tabBarItems,1);
	return true;
}

//顶部钻石、金币导航条初始化
bool ShopLayer::initTopMenuBar(){
	CCSprite* s_diamondInformationSpr = CCSprite::create("shop/diamondInformation.png");
	if (!s_diamondInformationSpr) return false;
	CCSprite* s_coinInformationSpr = CCSprite::create("shop/coinInformation.png");
	if (!s_coinInformationSpr) return false;

	s_diamondInformationSpr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamondInformationSpr->getContentSize().width / 2 + 380, s_diamondInformationSpr->getContentSize().height / 2 + 16)));
	s_coinInformationSpr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coinInformationSpr->getContentSize().width / 2 + 660, s_coinInformationSpr->getContentSize().height / 2 + 16)));
	
	//初始化钻石、金币数量
	char buf[100] = { 0 };
	sprintf(buf, "%d", m_diamond);
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond->getContentSize().width / 2 + 430, m_lblDiamond->getContentSize().height / 2 + 26)));
	this->addChild(m_lblDiamond);
	
	sprintf(buf, "%d", m_money);
	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin->getContentSize().width / 2 + 700, m_lblCoin->getContentSize().height / 2 + 26)));
	this->addChild(m_lblCoin);

	this->addChild(s_diamondInformationSpr);
	this->addChild(s_coinInformationSpr);

	//创建2个MenuItemSprite
	auto diamondAdd = MenuItemSprite::create(Sprite::create("shop/diamondAdd-normal.png"), Sprite::create("shop/diamondAdd-pressed.png"), CC_CALLBACK_1(ShopLayer::tapBarMenuPressed, this));
	diamondAdd->setTag(0);
	auto coinAdd = MenuItemSprite::create(Sprite::create("shop/coinAdd-normal.png"), Sprite::create("shop/coinAdd-pressed.png"), CC_CALLBACK_1(ShopLayer::tapBarMenuPressed, this));
	coinAdd->setTag(1);

	tabBarTopItems = Menu::create(diamondAdd, coinAdd, NULL);
	tabBarTopItems->alignItemsHorizontallyWithPadding(230);
	tabBarTopItems->setPosition(Director::getInstance()->convertToUI(Vec2(tabBarTopItems->getContentSize().width / 2 + 145, 40)));
	this->addChild(tabBarTopItems);

	return true;
}

//商城图标、返回按钮初始化
bool ShopLayer::initButtons(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* s_shopLogoSpr = CCSprite::create("shop/shoplogo.png");
	if (!s_shopLogoSpr) return false;
	Button* s_shopBackBtn = Button::create("shop/shopback-normal.png", "shop/shopback-pressed.png");
	if (!s_shopBackBtn) return false;

	s_shopBackBtn->setTag(TAG_BACK_BIN);

	s_shopBackBtn->setScale9Enabled(true);

	s_shopLogoSpr->setPosition(Director::getInstance()->convertToUI(Vec2(s_shopLogoSpr->getContentSize().width / 2, s_shopLogoSpr->getContentSize().height / 2)));
	s_shopBackBtn->setPosition(Director::getInstance()->convertToUI(Vec2(s_shopBackBtn->getContentSize().width / 2 + 1045, s_shopBackBtn->getContentSize().height / 2 + 8)));
	
	s_shopBackBtn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch,this));

	this->addChild(s_shopLogoSpr);
	this->addChild(s_shopBackBtn);

	return true;
}

//初始化物品显示框
bool ShopLayer::initShow(){
	CCSprite* s_show01Spr = CCSprite::create("shop/show01.png");
	if (!s_show01Spr) return false;
	CCSprite* s_show02Spr = CCSprite::create("shop/show02.png");
	if (!s_show02Spr) return false;
	CCSprite* s_show03Spr = CCSprite::create("shop/show03.png");
	if (!s_show03Spr) return false;
	CCSprite* s_show04Spr = CCSprite::create("shop/show04.png");
	if (!s_show04Spr) return false;
	CCSprite* s_show05Spr = CCSprite::create("shop/show05.png");
	if (!s_show05Spr) return false;
	CCSprite* s_show06Spr = CCSprite::create("shop/show06.png");
	if (!s_show06Spr) return false;

	s_show01Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show01Spr->getContentSize().width / 2 + 350, s_show01Spr->getContentSize().height / 2 + 120)));
	s_show02Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show02Spr->getContentSize().width / 2 + 620, s_show02Spr->getContentSize().height / 2 + 120)));
	s_show03Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show03Spr->getContentSize().width / 2 + 890, s_show03Spr->getContentSize().height / 2 + 120)));
	s_show04Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show04Spr->getContentSize().width / 2 + 350, s_show04Spr->getContentSize().height / 2 + 380)));
	s_show05Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show05Spr->getContentSize().width / 2 + 620, s_show05Spr->getContentSize().height / 2 + 380)));
	s_show06Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_show06Spr->getContentSize().width / 2 + 890, s_show06Spr->getContentSize().height / 2 + 380)));

	this->addChild(s_show01Spr);
	this->addChild(s_show02Spr);
	this->addChild(s_show03Spr);
	this->addChild(s_show04Spr);
	this->addChild(s_show05Spr);
	this->addChild(s_show06Spr);
	
	return true;
}

//初始化钻石层
bool ShopLayer::initDiamondLayer(){
	//获取需要变的颜色
	buyCoin->setColor(ccColor3B(colBegan.r * 0.65, colBegan.g * 0.65, colBegan.b * 0.65));

	//初始化钻石图片
	CCSprite* s_diamond01Spr = CCSprite::create("shop/diamond01.png");
	if (!s_diamond01Spr) return false;
	CCSprite* s_diamond02Spr = CCSprite::create("shop/diamond02.png");
	if (!s_diamond02Spr) return false;
	CCSprite* s_diamond03Spr = CCSprite::create("shop/diamond03.png");
	if (!s_diamond03Spr) return false;
	CCSprite* s_diamond04Spr = CCSprite::create("shop/diamond04.png");
	if (!s_diamond04Spr) return false;
	CCSprite* s_diamond05Spr = CCSprite::create("shop/diamond05.png");
	if (!s_diamond05Spr) return false;
	CCSprite* s_diamond06Spr = CCSprite::create("shop/diamond06.png");
	if (!s_diamond06Spr) return false;
	
	//初始化钻石购买数量
	m_lblDiamond01 = LabelTTF::create("60", "Arial", 24);
	m_lblDiamond01->setColor(Color3B(224, 179, 9));
	m_lblDiamond02 = LabelTTF::create("390", "Arial", 24);
	m_lblDiamond02->setColor(Color3B(224, 179, 9));
	m_lblDiamond03 = LabelTTF::create("800", "Arial", 24);
	m_lblDiamond03->setColor(Color3B(224, 179, 9));
	m_lblDiamond04 = LabelTTF::create("1500", "Arial", 24);
	m_lblDiamond04->setColor(Color3B(224, 179, 9));
	m_lblDiamond05 = LabelTTF::create("3000", "Arial", 24);
	m_lblDiamond05->setColor(Color3B(224, 179, 9));
	m_lblDiamond06 = LabelTTF::create("9680", "Arial", 24);
	m_lblDiamond06->setColor(Color3B(224, 179, 9));	

	//初始化钻石购买按钮
	s_buyDiamond01Btn = Button::create("shop/buyDiamond01-normal.png", "shop/buyDiamond01-pressed.png");
	if (!s_buyDiamond01Btn) return false;
	s_buyDiamond02Btn = Button::create("shop/buyDiamond02-normal.png", "shop/buyDiamond02-pressed.png");
	if (!s_buyDiamond02Btn) return false;
	s_buyDiamond03Btn = Button::create("shop/buyDiamond03-normal.png", "shop/buyDiamond03-pressed.png");
	if (!s_buyDiamond03Btn) return false;
	s_buyDiamond04Btn = Button::create("shop/buyDiamond04-normal.png", "shop/buyDiamond04-pressed.png");
	if (!s_buyDiamond04Btn) return false;
	s_buyDiamond05Btn = Button::create("shop/buyDiamond05-normal.png", "shop/buyDiamond05-pressed.png");
	if (!s_buyDiamond05Btn) return false;
	s_buyDiamond06Btn = Button::create("shop/buyDiamond06-normal.png", "shop/buyDiamond06-pressed.png");
	if (!s_buyDiamond06Btn) return false;

	//初始化按钮钻石标题
	s_buyDiamond01Lab = LabelTTF::create("$  6", "tuffy_bold_italic-charmap.png", 24);
	s_buyDiamond02Lab = LabelTTF::create("$  30", "Arial", 24);
	s_buyDiamond03Lab = LabelTTF::create("$  60", "Arial", 24);
	s_buyDiamond04Lab = LabelTTF::create("$  108", "Arial", 24);
	s_buyDiamond05Lab = LabelTTF::create("$  208", "Arial", 24);
	s_buyDiamond06Lab = LabelTTF::create("$  618", "Arial", 24);

	//打开scale9可以拉伸图片  
	s_buyDiamond01Btn->setScale9Enabled(true);
	s_buyDiamond02Btn->setScale9Enabled(true);
	s_buyDiamond03Btn->setScale9Enabled(true);
	s_buyDiamond04Btn->setScale9Enabled(true);
	s_buyDiamond05Btn->setScale9Enabled(true);
	s_buyDiamond06Btn->setScale9Enabled(true);
	
	s_diamond01Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond01Spr->getContentSize().width / 2 + 420, s_diamond01Spr->getContentSize().height / 2 + 155)));
	s_diamond02Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond02Spr->getContentSize().width / 2 + 685, s_diamond02Spr->getContentSize().height / 2 + 155)));
	s_diamond03Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond03Spr->getContentSize().width / 2 + 945, s_diamond03Spr->getContentSize().height / 2 + 155)));
	s_diamond04Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond04Spr->getContentSize().width / 2 + 408, s_diamond04Spr->getContentSize().height / 2 + 408)));
	s_diamond05Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond05Spr->getContentSize().width / 2 + 678, s_diamond05Spr->getContentSize().height / 2 + 408)));
	s_diamond06Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_diamond06Spr->getContentSize().width / 2 + 938, s_diamond06Spr->getContentSize().height / 2 + 408)));
	
	m_lblDiamond01->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond01->getContentSize().width / 2 + 438, m_lblDiamond01->getContentSize().height / 2 + 250)));
	m_lblDiamond02->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond02->getContentSize().width / 2 + 700, m_lblDiamond02->getContentSize().height / 2 + 250)));
	m_lblDiamond03->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond03->getContentSize().width / 2 + 970, m_lblDiamond03->getContentSize().height / 2 + 250)));
	m_lblDiamond04->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond04->getContentSize().width / 2 + 423, m_lblDiamond04->getContentSize().height / 2 + 510)));
	m_lblDiamond05->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond05->getContentSize().width / 2 + 695, m_lblDiamond05->getContentSize().height / 2 + 510)));
	m_lblDiamond06->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblDiamond06->getContentSize().width / 2 + 965, m_lblDiamond06->getContentSize().height / 2 + 510)));
	
	s_buyDiamond01Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond01Btn->getContentSize().width / 2 + 375, s_buyDiamond01Btn->getContentSize().height / 2 + 295)));
	s_buyDiamond02Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond02Btn->getContentSize().width / 2 + 645, s_buyDiamond02Btn->getContentSize().height / 2 + 295)));
	s_buyDiamond03Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond03Btn->getContentSize().width / 2 + 915, s_buyDiamond03Btn->getContentSize().height / 2 + 295)));
	s_buyDiamond04Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond04Btn->getContentSize().width / 2 + 375, s_buyDiamond04Btn->getContentSize().height / 2 + 555)));
	s_buyDiamond05Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond05Btn->getContentSize().width / 2 + 645, s_buyDiamond05Btn->getContentSize().height / 2 + 555)));
	s_buyDiamond06Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond06Btn->getContentSize().width / 2 + 915, s_buyDiamond06Btn->getContentSize().height / 2 + 555)));

	s_buyDiamond01Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond01Lab->getContentSize().width / 2 + 60, s_buyDiamond01Lab->getContentSize().height / 2 + 590)));
	s_buyDiamond02Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond02Lab->getContentSize().width / 2 + 55, s_buyDiamond02Lab->getContentSize().height / 2 + 590)));
	s_buyDiamond03Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond03Lab->getContentSize().width / 2 + 55, s_buyDiamond03Lab->getContentSize().height / 2 + 590)));
	s_buyDiamond04Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond04Lab->getContentSize().width / 2 + 50, s_buyDiamond04Lab->getContentSize().height / 2 + 590)));
	s_buyDiamond05Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond05Lab->getContentSize().width / 2 + 50, s_buyDiamond05Lab->getContentSize().height / 2 + 590)));
	s_buyDiamond06Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyDiamond06Lab->getContentSize().width / 2 + 50, s_buyDiamond06Lab->getContentSize().height / 2 + 590)));

	//按钮标记
	s_buyDiamond01Btn->setTag(TAG_DIAMOND01_BIN);
	s_buyDiamond02Btn->setTag(TAG_DIAMOND02_BIN);
	s_buyDiamond03Btn->setTag(TAG_DIAMOND03_BIN);
	s_buyDiamond04Btn->setTag(TAG_DIAMOND04_BIN);
	s_buyDiamond05Btn->setTag(TAG_DIAMOND05_BIN);
	s_buyDiamond06Btn->setTag(TAG_DIAMOND06_BIN);

	//添加监听器

	s_buyDiamond01Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyDiamond02Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyDiamond03Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyDiamond04Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyDiamond05Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyDiamond06Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));

	s_buyDiamond01Btn->addChild(s_buyDiamond01Lab);
	s_buyDiamond02Btn->addChild(s_buyDiamond02Lab);
	s_buyDiamond03Btn->addChild(s_buyDiamond03Lab);
	s_buyDiamond04Btn->addChild(s_buyDiamond04Lab);
	s_buyDiamond05Btn->addChild(s_buyDiamond05Lab);
	s_buyDiamond06Btn->addChild(s_buyDiamond06Lab);

	layerDiamond->addChild(s_diamond01Spr);
	layerDiamond->addChild(s_diamond02Spr);
	layerDiamond->addChild(s_diamond03Spr);
	layerDiamond->addChild(s_diamond04Spr);
	layerDiamond->addChild(s_diamond05Spr);
	layerDiamond->addChild(s_diamond06Spr);
	layerDiamond->addChild(m_lblDiamond01);
	layerDiamond->addChild(m_lblDiamond02);
	layerDiamond->addChild(m_lblDiamond03);
	layerDiamond->addChild(m_lblDiamond04);
	layerDiamond->addChild(m_lblDiamond05);
	layerDiamond->addChild(m_lblDiamond06);
	layerDiamond->addChild(s_buyDiamond01Btn);
	layerDiamond->addChild(s_buyDiamond02Btn);
	layerDiamond->addChild(s_buyDiamond03Btn);
	layerDiamond->addChild(s_buyDiamond04Btn);
	layerDiamond->addChild(s_buyDiamond05Btn);
	layerDiamond->addChild(s_buyDiamond06Btn);
	


	return true;
}


//初始化金币层
bool ShopLayer::initCoinLayer(){
	layerCoin = Layer::create();

	//初始化金币图片
	CCSprite* s_coin01Spr = CCSprite::create("shop/coin01.png");
	if (!s_coin01Spr) return false;
	CCSprite* s_coin02Spr = CCSprite::create("shop/coin02.png");
	if (!s_coin02Spr) return false;
	CCSprite* s_coin03Spr = CCSprite::create("shop/coin03.png");
	if (!s_coin03Spr) return false;
	CCSprite* s_coin04Spr = CCSprite::create("shop/coin04.png");
	if (!s_coin04Spr) return false;
	CCSprite* s_coin05Spr = CCSprite::create("shop/coin05.png");
	if (!s_coin05Spr) return false;
	CCSprite* s_coin06Spr = CCSprite::create("shop/coin06.png");
	if (!s_coin06Spr) return false;
	
	//初始化金币购买数量
	m_lblCoin01 = LabelTTF::create("5万", "Arial", 24);
	m_lblCoin01->setColor(Color3B(224, 179, 9));
	m_lblCoin02 = LabelTTF::create("10万", "Arial", 24);
	m_lblCoin02->setColor(Color3B(224, 179, 9));
	m_lblCoin03 = LabelTTF::create("50万", "Arial", 24);
	m_lblCoin03->setColor(Color3B(224, 179, 9));
    m_lblCoin04 = LabelTTF::create("100万", "Arial", 24);
	m_lblCoin04->setColor(Color3B(224, 179, 9));
	m_lblCoin05 = LabelTTF::create("200万", "Arial", 24);
	m_lblCoin05->setColor(Color3B(224, 179, 9));
	m_lblCoin06 = LabelTTF::create("500万", "Arial", 24);
	m_lblCoin06->setColor(Color3B(224, 179, 9));
	
	//初始化金币购买按钮
	s_buyCoin01Btn = Button::create("shop/buyCoin01-normal.png", "shop/buyCoin01-pressed.png");
	if (!s_buyCoin01Btn) return false;
	s_buyCoin02Btn = Button::create("shop/buyCoin02-normal.png", "shop/buyCoin02-pressed.png");
	if (!s_buyCoin02Btn) return false;
	s_buyCoin03Btn = Button::create("shop/buyCoin03-normal.png", "shop/buyCoin03-pressed.png");
	if (!s_buyCoin03Btn) return false;
	s_buyCoin04Btn = Button::create("shop/buyCoin04-normal.png", "shop/buyCoin04-pressed.png");
	if (!s_buyCoin04Btn) return false;
	s_buyCoin05Btn = Button::create("shop/buyCoin05-normal.png", "shop/buyCoin05-pressed.png");
	if (!s_buyCoin05Btn) return false;
	s_buyCoin06Btn = Button::create("shop/buyCoin06-normal.png", "shop/buyCoin06-pressed.png");
	if (!s_buyCoin06Btn) return false;

	//初始化按钮标题金币
	LabelTTF* s_buyCoin01Lab = LabelTTF::create("钻石  50", "Arial", 24);
	LabelTTF* s_buyCoin02Lab = LabelTTF::create("钻石  100", "Arial", 24);
	LabelTTF* s_buyCoin03Lab = LabelTTF::create("钻石  500", "Arial", 24);
	LabelTTF* s_buyCoin04Lab = LabelTTF::create("钻石  1000", "Arial", 24);
	LabelTTF* s_buyCoin05Lab = LabelTTF::create("钻石  2000", "Arial", 24);
	LabelTTF* s_buyCoin06Lab = LabelTTF::create("钻石  5000", "Arial", 24);

	//打开scale9可以拉伸图片  
	s_buyCoin01Btn->setScale9Enabled(true);
	s_buyCoin02Btn->setScale9Enabled(true);
	s_buyCoin03Btn->setScale9Enabled(true);
	s_buyCoin04Btn->setScale9Enabled(true);
	s_buyCoin05Btn->setScale9Enabled(true);
	s_buyCoin06Btn->setScale9Enabled(true);

	s_coin01Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin01Spr->getContentSize().width / 2 + 420, s_coin01Spr->getContentSize().height / 2 + 155)));
	s_coin02Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin02Spr->getContentSize().width / 2 + 685, s_coin02Spr->getContentSize().height / 2 + 155)));
	s_coin03Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin03Spr->getContentSize().width / 2 + 945, s_coin03Spr->getContentSize().height / 2 + 155)));
	s_coin04Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin04Spr->getContentSize().width / 2 + 405, s_coin04Spr->getContentSize().height / 2 + 400)));
	s_coin05Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin05Spr->getContentSize().width / 2 + 685, s_coin05Spr->getContentSize().height / 2 + 400)));
	s_coin06Spr->setPosition(Director::getInstance()->convertToUI(Vec2(s_coin06Spr->getContentSize().width / 2 + 950, s_coin06Spr->getContentSize().height / 2 + 400)));
	
	m_lblCoin01->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin01->getContentSize().width / 2 + 438, m_lblCoin01->getContentSize().height / 2 + 250)));
	m_lblCoin02->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin02->getContentSize().width / 2 + 700, m_lblCoin02->getContentSize().height / 2 + 250)));
	m_lblCoin03->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin03->getContentSize().width / 2 + 970, m_lblCoin03->getContentSize().height / 2 + 250)));
	m_lblCoin04->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin04->getContentSize().width / 2 + 423, m_lblCoin04->getContentSize().height / 2 + 510)));
	m_lblCoin05->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin05->getContentSize().width / 2 + 695, m_lblCoin05->getContentSize().height / 2 + 510)));
	m_lblCoin06->setPosition(Director::getInstance()->convertToUI(Vec2(m_lblCoin06->getContentSize().width / 2 + 965, m_lblCoin06->getContentSize().height / 2 + 510)));
	
	s_buyCoin01Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin01Btn->getContentSize().width / 2 + 375, s_buyCoin01Btn->getContentSize().height / 2 + 295)));
	s_buyCoin02Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin02Btn->getContentSize().width / 2 + 645, s_buyCoin02Btn->getContentSize().height / 2 + 295)));
	s_buyCoin03Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin03Btn->getContentSize().width / 2 + 915, s_buyCoin03Btn->getContentSize().height / 2 + 295)));
	s_buyCoin04Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin04Btn->getContentSize().width / 2 + 375, s_buyCoin04Btn->getContentSize().height / 2 + 555)));
	s_buyCoin05Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin05Btn->getContentSize().width / 2 + 645, s_buyCoin05Btn->getContentSize().height / 2 + 555)));
	s_buyCoin06Btn->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin06Btn->getContentSize().width / 2 + 915, s_buyCoin06Btn->getContentSize().height / 2 + 555)));

	s_buyCoin01Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin01Lab->getContentSize().width / 2 + 50, s_buyCoin01Lab->getContentSize().height / 2 + 590)));
	s_buyCoin02Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin02Lab->getContentSize().width / 2 + 50, s_buyCoin02Lab->getContentSize().height / 2 + 590)));
	s_buyCoin03Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin03Lab->getContentSize().width / 2 + 50, s_buyCoin03Lab->getContentSize().height / 2 + 590)));
	s_buyCoin04Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin04Lab->getContentSize().width / 2 + 40, s_buyCoin04Lab->getContentSize().height / 2 + 590)));
	s_buyCoin05Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin05Lab->getContentSize().width / 2 + 40, s_buyCoin05Lab->getContentSize().height / 2 + 590)));
	s_buyCoin06Lab->setPosition(Director::getInstance()->convertToUI(Vec2(s_buyCoin06Lab->getContentSize().width / 2 + 40, s_buyCoin06Lab->getContentSize().height / 2 + 590)));
	
	//按钮标记
	s_buyCoin01Btn->setTag(TAG_COIN01_BIN);
	s_buyCoin02Btn->setTag(TAG_COIN02_BIN);
	s_buyCoin03Btn->setTag(TAG_COIN03_BIN);
	s_buyCoin04Btn->setTag(TAG_COIN04_BIN);
	s_buyCoin05Btn->setTag(TAG_COIN05_BIN);
	s_buyCoin06Btn->setTag(TAG_COIN06_BIN);

	//添加监听器
	s_buyCoin01Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyCoin02Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyCoin03Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyCoin04Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyCoin05Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));
	s_buyCoin06Btn->addTouchEventListener(CC_CALLBACK_2(ShopLayer::onBtnTouch, this));


	s_buyCoin01Btn->addChild(s_buyCoin01Lab);
	s_buyCoin02Btn->addChild(s_buyCoin02Lab);
	s_buyCoin03Btn->addChild(s_buyCoin03Lab);
	s_buyCoin04Btn->addChild(s_buyCoin04Lab);
	s_buyCoin05Btn->addChild(s_buyCoin05Lab);
	s_buyCoin06Btn->addChild(s_buyCoin06Lab);

	layerCoin->addChild(s_coin01Spr);
	layerCoin->addChild(s_coin02Spr);
	layerCoin->addChild(s_coin03Spr);
	layerCoin->addChild(s_coin04Spr);
	layerCoin->addChild(s_coin05Spr);
	layerCoin->addChild(s_coin06Spr);
	layerCoin->addChild(m_lblCoin01);
	layerCoin->addChild(m_lblCoin02);
	layerCoin->addChild(m_lblCoin03);
	layerCoin->addChild(m_lblCoin04);
	layerCoin->addChild(m_lblCoin05);
	layerCoin->addChild(m_lblCoin06);
	layerCoin->addChild(s_buyCoin01Btn);
	layerCoin->addChild(s_buyCoin02Btn);
	layerCoin->addChild(s_buyCoin03Btn);
	layerCoin->addChild(s_buyCoin04Btn);
	layerCoin->addChild(s_buyCoin05Btn);
	layerCoin->addChild(s_buyCoin06Btn);

	return true;
}



//void ShopLayer::onEnter()
//{
//	CCLayer::onEnter();
//
//	//static_cast<MenuItemSprite *>(tabBarItems->getChildByTag(0))->selected();
//}

void ShopLayer::tapBarMenuPressed(Ref *pSender)
{
	auto toolbar = (MenuItemSprite *)pSender;
	//toolbar->selected();
	//通过获取item的tag决定切换到哪个layer
	if (toolbar->getTag() == 0)
	{
		layerDiamond->setVisible(true);
		layerCoin->setVisible(false);
	}
	else
	{
		layerDiamond->setVisible(false);
		layerCoin->setVisible(true);
	}
	if (toolbar->getTag() == 0){
		buyDiamond->setColor(ccColor3B(colBegan.r, colBegan.g, colBegan.b));
		buyCoin->setColor(ccColor3B(colBegan.r * 0.60, colBegan.g * 0.60, colBegan.b * 0.60));
	}
	else if (toolbar->getTag() == 1){
		//获取需要变的颜色
		buyDiamond->setColor(ccColor3B(colBegan.r * 0.60, colBegan.g * 0.60, colBegan.b * 0.60));
		buyCoin->setColor(ccColor3B(colBegan.r, colBegan.g, colBegan.b));
	}
	//切换到相应的layer 并把之前selected 的改成unselected状态
	/*for (int i = 0; i < tabBarItems->getChildren().size(); i++){
		auto tmpbar = dynamic_cast<MenuItemSprite *>(tabBarItems->getChildren().at(i));
			if(tmpbar != NULL && tmpbar->getTag() != toolbar->getTag()) {
				tmpbar->unselected();
			}
	}*/
}


//触摸监听
void ShopLayer::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case TAG_BACK_BIN:
		{
			log("back");
			Director::getInstance()->replaceScene(MainScene::scene(m_playerID));
			break;
		}
		case TAG_DIAMOND01_BIN:
		{

			//AudioManager::getInstance()->fileConvertedToBinary_Send("C:\\Users\\Administrator\\Desktop\\target.mp3");
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)	//判断当前平台为ios平台
						log("录音");
						m_recordObject->StartRecord();
			#endif

			#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
				CCLog("jni-java函数recordAudio执行完毕");
			#endif

			log("DIAMOND1");
			auto diamond01Value = m_lblDiamond01->getString().c_str();
			auto s_buyDiamond01LabValue = s_buyDiamond01Lab->getString().c_str();		
			CCLOG("diamond01Value=%s", diamond01Value);	
			CCLOG("s_buyDiamond01LabValue=%s", s_buyDiamond01LabValue);
			S_ZZ_WechatOrderReq s(0, 60);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_DIAMOND02_BIN:
		{
			log("DIAMOND2");
			auto diamond02Value = m_lblDiamond02->getString().c_str();
			CCLOG("offset=%s", diamond02Value);
			S_ZZ_WechatOrderReq s(0, 390);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_DIAMOND03_BIN:
		{
			log("DIAMOND3");
			auto diamond03Value = m_lblDiamond03->getString().c_str();
			CCLOG("offset=%s", diamond03Value);
			S_ZZ_WechatOrderReq s(0, 800);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_DIAMOND04_BIN:
		{
			log("DIAMOND4");
			auto diamond04Value = m_lblDiamond04->getString().c_str();
			CCLOG("offset=%s", diamond04Value);
			S_ZZ_WechatOrderReq s(0, 1500);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_DIAMOND05_BIN:
		{
			log("DIAMOND5");
			auto diamond05Value = m_lblDiamond05->getString().c_str();
			CCLOG("offset=%s", diamond05Value);
			S_ZZ_WechatOrderReq s(0, 3000);
			NetworkManger::getInstance()->SendRequest(s);
			break;

		}
		case TAG_DIAMOND06_BIN:
		{
			log("DIAMOND6");
			auto diamond06Value = m_lblDiamond06->getString().c_str();
			CCLOG("offset=%s", diamond06Value);
			S_ZZ_WechatOrderReq s(0, 9680);
			NetworkManger::getInstance()->SendRequest(s);
			break;

		}
		case TAG_COIN01_BIN:
		{
			log("COIN1");
			auto coin01Value = m_lblCoin01->getString().c_str();
			CCLOG("offset=%s", coin01Value);
			S_ZZ_WechatOrderReq s(1, 50);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_COIN02_BIN:
		{
			log("COIN2");
			auto coin02Value = m_lblCoin02->getString().c_str();
			CCLOG("offset=%s", coin02Value);
			S_ZZ_WechatOrderReq s(1, 100);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_COIN03_BIN:
		{
			log("COIN3");
			auto coin03Value = m_lblCoin03->getString().c_str();
			CCLOG("offset=%s", coin03Value);
			S_ZZ_WechatOrderReq s(1, 500);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_COIN04_BIN:
		{
			log("COIN4");
			auto coin04Value = m_lblCoin04->getString().c_str();
			CCLOG("offset=%s", coin04Value);
			S_ZZ_WechatOrderReq s(1, 1000);
			NetworkManger::getInstance()->SendRequest(s);
			break;
		}
		case TAG_COIN05_BIN:
		{
			log("COIN5");
			auto coin05Value = m_lblCoin05->getString().c_str();
			CCLOG("offset=%s", coin05Value);
			S_ZZ_WechatOrderReq s(1, 2000);
			NetworkManger::getInstance()->SendRequest(s);
			break;

		}
		case TAG_COIN06_BIN:
		{
			log("COIN6");
			auto coin06Value = m_lblCoin06->getString().c_str();
			CCLOG("offset=%s", coin06Value);
			S_ZZ_WechatOrderReq s(1, 5000);
			NetworkManger::getInstance()->SendRequest(s);
			break;

		}
		}
	}
}