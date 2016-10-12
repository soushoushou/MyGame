#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "constString.h"
#include "Global.h"
#include "NiuPoker.h"
#include "NiuPlayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CDMRecordObject.h"
#endif

USING_NS_CC;

bool isRecording;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
CDMRecordObject *m_recordObject;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif


enum ButtonTag{
    /** 准备 */
    TAG_START_BTN=1,
    /** 不抢 */
    TAG_NOT_HOG_BTN,
    /** 抢庄 */
    TAG_HOG_BTN,
    /** 一倍按钮 */
    TAG_MUL_ONE,
    /** 二倍按钮 */
    TAG_MUL_TWO,
    /** 三倍按钮 */
    TAG_MUL_THERE,
    /** 四倍按钮 */
    TAG_MUL_FOUR,
    /** 五倍按钮 */
    TAG_MUL_FIVE,
	/** 聊天 */
	TAG_CHAT_BTN,
    /** 录音 */
    TAG_RECORD_BTN
};


GamePlayScene::GamePlayScene(unsigned long long playerID,int roomID) :m_timeLayer(NULL), m_startGameBtn(NULL), m_bReady(false), m_isSend(true),
m_iSendPk(0), m_iState(StartState), m_btnSetting(NULL), m_pUser(NULL), m_pUserLeft(NULL), m_pUserRight(NULL), m_pUserTopLeft(NULL),
m_pUserTopRight(NULL), m_playerID(playerID), m_roomID(roomID)
{
    m_player = new NiuPlayer();
    m_playerRight = new NiuPlayer();
    m_playerTopRight = new NiuPlayer();
    m_playerTopLeft = new NiuPlayer();
	m_playerLeft = new NiuPlayer();

	m_arrPokers = __Array::create();
	m_arrPokers->retain();
    m_creatHogBtn=false;
    m_creatMulBtn=false;
    m_playNum=1;
}

GamePlayScene::~GamePlayScene(){
	DebugSimpleServer::getInstance()->quitRoom("alw");
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_playerRight);
	CC_SAFE_DELETE(m_playerTopRight);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_RELEASE(m_arrPokers);
	CC_SAFE_RELEASE(m_btnSetting);
	
}

GamePlayScene* GamePlayScene::create(unsigned long long playerID,int roomID)
{

	GamePlayScene *pRet = new(std::nothrow) GamePlayScene(playerID,roomID); 
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


Scene* GamePlayScene::createScene(unsigned long long playerID,int roomID)
{
	auto scene = Scene::create();
	auto gamePlayScene = GamePlayScene::create(playerID,roomID);
	scene->addChild(gamePlayScene);
	return scene;
}

void GamePlayScene::update(float delta)
{
	cocos2d::Size Size = Director::sharedDirector()->getWinSize();
	auto server = DebugSimpleServer::getInstance();


	switch (m_iState)
	{
        case StartState:
        {
		    //倒计时
            if (server->isAllReady())
            {
                if (!m_timeLayer && m_bReady)
                {
                    m_timeLayer = TimeLayer::create();
                    addChild(m_timeLayer,50);
                }
                if (m_timeLayer && m_timeLayer->canRemove())
                {
                    m_timeLayer->setVisible(false);
                    m_startGameBtn->setVisible(false);
                    m_iState = SendPokerState;
                }
            }
            break;
        }
        case SendPokerState:
			//发牌
            SendPk();
            break;
        case HogState:{
            if (m_timeLayer && m_timeLayer->canRemove())
            {
                notHogBtnAction();
                unschedule(schedule_selector(GamePlayScene::update));
            }
            break;
        }
        case ChooseMultipleState:{
            if (m_timeLayer && m_timeLayer->canRemove())
            {
                notChooseMulAction(0);
                unschedule(schedule_selector(GamePlayScene::update));
            }
            break;
            
        }
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
	if (!initPlayerProfile()) return false;	//初始化玩家信息
	if (!initPlayerLeftProfile()) return false;	//初始化左侧玩家信息
	if (!initPlayerRightProfile()) return false;	//初始化左侧玩家信息
	if (!initPlayerTopLeftProfile()) return false;	//初始化顶部左侧玩家信息
	if (!initPlayerTopRightProfile()) return false;	//初始化顶部左侧玩家信息
	srand((unsigned)time(NULL));//初始化随机种子
	if (!initPlayer()) return false;
	if (!createPokers()) return false;
	if (!xiPai()) return false;
    schedule(schedule_selector(GamePlayScene::update));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isRecording=false;
    m_recordObject=new CDMRecordObject();
#endif
	return true;
}

//初始化背景
bool GamePlayScene::initBackground()
{
	auto size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	auto spriteBK = Sprite::create("game/gamebg.png");
	spriteBK->setPosition(cocos2d::Point(size.width / 2, size.height / 2));
	this->addChild(spriteBK);
    
	char buf[100] = { 0 };
	sprintf(buf, "房间号:%d", m_roomID);
    m_pRoomNumberLabel = Label::create(buf, "Arial", 25);
    if (!m_pRoomNumberLabel) return false;
    m_pRoomNumberLabel->setPosition(Vec2(size.width / 2 - 270, size.height / 2 + 290));
    m_pRoomNumberLabel->setColor(Color3B(128, 85, 30));
    this->addChild(m_pRoomNumberLabel);
    
    m_pNoticeLabel = LabelTTF::create("第1局", "Arial", 25);
    if (!m_pNoticeLabel) return false;
    m_pNoticeLabel->setPosition(Vec2(size.width / 2,size.height / 2 + 290));
	m_pNoticeLabel->setColor(Color3B(128, 85, 30));
    this->addChild(m_pNoticeLabel);
    
    m_pModelLabel = LabelTTF::create("模式:抢庄模式", "Arial", 25);
    if (!m_pModelLabel) return false;
    m_pModelLabel->setPosition(Vec2(size.width / 2 + 270, size.height / 2 + 290));
	m_pModelLabel->setColor(Color3B(220, 163, 59));
    this->addChild(m_pModelLabel);
	return true;
}

bool GamePlayScene::initButtons()
{
	auto Size = Director::getInstance()->getVisibleSize();

	//开始游戏按钮
	m_startGameBtn = Button::create("game/startgame.png");
	if (!m_startGameBtn) return false;
	m_startGameBtn->setTag(TAG_START_BTN);
	m_startGameBtn->setScale9Enabled(true);
	m_startGameBtn->setPosition(cocos2d::Vec2(Size.width / 2, Size.height / 2 - 150));
	m_startGameBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
	this->addChild(m_startGameBtn,51);

	//设置按钮
	m_btnSetting = new SettingMenuInPlaying(this,Director::getInstance()->convertToUI(Vec2(980 + 68.5, 22)));
    m_btnSetting->retain();

	//聊天按钮
	m_chatBtn = Button::create("game/chat.png");
	m_chatBtn->setTag(TAG_CHAT_BTN);
	m_chatBtn->setScale9Enabled(true);
	m_chatBtn->setPosition(Vec2(Size.width - 200, 80));
	m_chatBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
	this->addChild(m_chatBtn,100);

	//语音按钮
    m_recordBtn = Button::create("game/record.png","game/record-pressed.png");
    m_recordBtn->setTag(TAG_RECORD_BTN);
    m_recordBtn->setScale9Enabled(true);
    m_recordBtn->setPosition(Vec2(Size.width - 100, 80));
    m_recordBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
    this->addChild(m_recordBtn,100);
    
	return true;
}

bool GamePlayScene::initPlayerProfile()
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
	if (!m_pUser)
	{
		m_pUser = new HerizelUserProfileUI(this);
		m_pUser->setProfileProperty(cocos2d::Vec2(160, 550), "MainScene/timo.png", "LOVEVVV666", 13300, 13333, 2);
	}
	//S_GetPlayerInfoReq gpi(m_playerID);
	//NetworkManger::getInstance()->SendRequest_GetPlayerInfo(gpi);
	return true;
}

bool GamePlayScene::initPlayerLeftProfile()
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
	if (!m_pUserLeft)
	{
		m_pUserLeft = VerticalUserProfileUI::create(this);
		m_pUserLeft->setProfileProperty(cocos2d::Vec2(80, 330), "MainScene/timo.png", "MM", 13300, 13333, 1);
		m_pUserLeft->showBanker(true);
		m_pUserLeft->showMultiple(true);
	}
	return true;
}

bool GamePlayScene::initPlayerRightProfile()
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
	if (!m_pUserRight)
	{
		m_pUserRight = VerticalUserProfileUI::create(this);
		m_pUserRight->setProfileProperty(cocos2d::Vec2(1050, 330), "MainScene/timo.png", "GG", 10000, 1333, 1);
		//m_pUserRight->showBanker(true);
		m_pUserRight->showMultiple(true);
	}
	return true;
}

bool GamePlayScene::initPlayerTopLeftProfile()
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
	if (!m_pUserTopLeft)
	{
		m_pUserTopLeft = HerizelUserProfileUI::create(this);
		m_pUserTopLeft->setProfileProperty(cocos2d::Vec2(400, 130), "MainScene/timo.png", "sicong", 17000, 1400, 3);
	}
	return true;
}

bool GamePlayScene::initPlayerTopRightProfile()
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
	if (!m_pUserTopRight)
	{
		m_pUserTopRight = HerizelUserProfileUI::create(this);
		m_pUserTopRight->setProfileProperty(cocos2d::Vec2(760, 130), "MainScene/timo.png", "jianlin", 17000, 1400, 3);
	}
	return true;
}

void GamePlayScene::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	cocos2d::Size Size = Director::getInstance()->getWinSize();
    Button* button = (Button*)pSender;
    unsigned int tag = button->getTag();
    if (type == Widget::TouchEventType::BEGAN) {
        switch (tag)
        {
            case TAG_RECORD_BTN:{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)	//判断当前平台为ios平台
					log("录音");
					m_recordObject->StartRecord();
				#endif

				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
					JniMethodInfo minfo;//定义Jni函数信息结构体
					//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
					bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/video/android/Audio", "recordAudio", "()V");

					if (!isHave) {
						CCLog("jni:此函数不存在");
					}else{
						CCLog("jni:此函数存在");
						//调用此函数
						minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,823);
					}
					CCLog("jni-java函数执行完毕");
				#endif
            }
                break;
            default:
                break;
        }
    }
	else if (type == Widget::TouchEventType::ENDED)
	{
		switch (tag)
		{
            case TAG_START_BTN:
            {
                log("start game");
				button->setTouchEnabled(false);
				button->loadTextures("game/startgamePressed.png", "");
				//模拟当所有玩家都准备好后再倒计时
				m_bReady = !m_bReady;
				DebugSimpleServer::getInstance()->playerReady("alw");
                break;
            }
            case TAG_HOG_BTN:
            {
                notHogBtnAction();
                break;
            }
            case TAG_NOT_HOG_BTN:
            {
                m_notHogBtn->setVisible(false);
                m_HogBtn->setVisible(false);
                m_timeLayer->stopTimer();
                m_iState=ChooseMultipleState;
                showChooseMultipleButton();
                break;
            }
            case TAG_MUL_ONE:
            case TAG_MUL_TWO:
            case TAG_MUL_THERE:
            case TAG_MUL_FOUR:
            case TAG_MUL_FIVE:{
                notChooseMulAction(0);
//                m_player->showMulti(tag-TAG_MUL_ONE+1,this);
//                scheduleOnce(schedule_selector(GamePlayScene::notChooseMulAction), 10.0f);
                break;
            }
			case TAG_CHAT_BTN:
			{
				log("chat");
				auto Size = Director::getInstance()->getWinSize();
				m_chatLayer = ChatLayer::create();

				//快捷聊天内容以及音乐地址
				vector<pair<string, string>> quickMessage;
				quickMessage.push_back(pair<string, string>("play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play game", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("play game play", "game/message1.mp3"));

				m_chatLayer->createListView(quickMessage);

				addChild(m_chatLayer,500);
				break;
			}
            case TAG_RECORD_BTN:{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					m_recordObject->StartPlay();
				#endif
            
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
					JniMethodInfo minfo;//定义Jni函数信息结构体
					//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
					bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/video/android/Audio", "startPlay", "()V");

					if (!isHave) {
						CCLog("jni:此函数不存在");
					}else{
						CCLog("jni:此函数存在");
						//调用此函数
						minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,823);
					}
					CCLog("jni-java函数执行完毕");
				#endif
			
                break;
			}
            default:
                break;
		}
	}
}

bool GamePlayScene::initPlayer(){
	cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	//设置主玩家的位置
    m_player->setPoint(cocos2d::Vec2(Size.width / 2, Size.height / 6-20));
    m_player->setPlayerClass(PlayerType_Me);
    //设置玩家右的位置
    m_playerRight->setPoint(cocos2d::Vec2(Size.width - pkWidth_small * 3 - 180, Size.height / 2 - 30));
    m_playerRight->setPlayerClass(PlayerType_Right);
    //设置玩家上二的位置
    m_playerTopRight->setPoint(cocos2d::Vec2(Size.width*0.5 + pkWidth_small * 3 - 100, Size.height / 6 * 5 - 130));
    m_playerTopRight->setPlayerClass(PlayerType_TopRight);
    //设置玩家上一的位置
    m_playerTopLeft->setPoint(Vec2(Size.width*0.5 - pkWidth_small * 4 - 20, Size.height / 6 * 5 - 130));
    m_playerTopLeft->setPlayerClass(PlayerType_TopLeft);
    //设置玩家左的位置
    m_playerLeft->setPoint(Vec2(165, Size.height / 2 - 30));
    m_playerLeft->setPlayerClass(PlayerType_Left);

	return true;
}

NiuPoker* GamePlayScene::selectPoker(int huaSe, int num){
	NiuPoker* pk;
    char path[256] = { 0 };
    sprintf(path, "pokerBig/%d_%d@2x.png", huaSe,num);
    pk = NiuPoker::create("poker.png", cocos2d::Rect(0, 0, pkWidth_small, pkHeight_small));
    pk->setHuaSe(huaSe);
	pk->setNum(num);
	pk->setGameMain(this);
	return pk;
}

bool GamePlayScene::createPokers(){
	bool isRet = false;
	do
	{
		NiuPoker* pk;
		//创建52个牌
		for (int i = 1; i<=4; ++i)
		{
			for (int j = 1; j <= 13; ++j)
			{
				pk = selectPoker(i, j);
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
                pk->setVisible(false);
			}
		}
		isRet = true;
	} while (0);
	return isRet;
}
#pragma mark-洗牌
bool GamePlayScene::xiPai(){
    cocos2d::Size Size = Director::getInstance()->getVisibleSize();
	bool isRet = false;
	do
	{
		for (int i = 0; i<52; ++i)
		{
			NiuPoker* pk1 = (NiuPoker*)m_arrPokers->getRandomObject();
			NiuPoker* pk2 = (NiuPoker*)m_arrPokers->getRandomObject();
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		isRet = true;
	} while (0);
    for (int i=0; i<25; i++) {
        NiuPoker* pk = (NiuPoker*)m_arrPokers->getObjectAtIndex(i);
        pk->setPosition(Vec2(Size.width / 2, Size.height / 2));
        pk->showLast();
        pk->setVisible(true);
    }
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
    else{
        m_iState = HogState;
        showHogButton();
    }
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

#pragma mark-显示抢庄按钮
void GamePlayScene::showHogButton()
{
    m_timeLayer->setTimeAndType(12, Tip_hog);
    if (!m_creatHogBtn) {
        auto Size = Director::getInstance()->getVisibleSize();
        /** 不抢 */
        m_notHogBtn = Button::create("game/not_hog_button.png","game/not_hog_button_pressed.png");
        
        m_notHogBtn->setTag(TAG_NOT_HOG_BTN);
        
        m_notHogBtn->setScale9Enabled(true);
        
        m_notHogBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        
        this->addChild(m_notHogBtn,51);
        /** 抢庄 */
        m_HogBtn = Button::create("game/hog_button.png","game/hog_button_pressed.png");
        
        m_HogBtn->setTag(TAG_HOG_BTN);
        
        m_HogBtn->setScale9Enabled(true);
        
        m_HogBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        
        this->addChild(m_HogBtn,51);
        
        float btnwidth=m_notHogBtn->getContentSize().width;
        float height=Size.height *0.5 - 150;
        m_notHogBtn->setPosition(Vec2(Size.width / 2-(btnwidth*0.5+10), height));
        m_HogBtn->setPosition(Vec2(Size.width / 2+(btnwidth*0.5+10), height));
        
        m_creatHogBtn=true;
    }
    else
    {
        m_notHogBtn->setVisible(true);
        m_HogBtn->setVisible(true);
    }
    
}

#pragma mark-不抢事件
void GamePlayScene::notHogBtnAction(){
    m_notHogBtn->setVisible(false);
    m_HogBtn->setVisible(false);
    m_timeLayer->stopTimer();
    m_iState=CompareState;
    showCompare();
}

#pragma mark-显示倍数按钮
void GamePlayScene::showChooseMultipleButton()
{
    m_timeLayer->setTimeAndType(12, Tip_chooseMul);
    schedule(schedule_selector(GamePlayScene::update));
    if (!m_creatMulBtn) {
        auto Size = Director::getInstance()->getVisibleSize();
        /** 一倍 */
        m_OneBtn = Button::create("game/button_02.png","game/button-pressed_02.png");
        m_OneBtn->setScale9Enabled(true);
        m_OneBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_OneBtn,51);
        /** 二倍 */
        m_TwoBtn = Button::create("game/button_05.png","game/button-pressed_05.png");
        m_TwoBtn->setScale9Enabled(true);
        m_TwoBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_TwoBtn,51);
        /** 三倍 */
        m_ThreeBtn = Button::create("game/button_07.png","game/button-pressed_07.png");
        m_ThreeBtn->setScale9Enabled(true);
        m_ThreeBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_ThreeBtn,51);
        /** 四倍 */
        m_FourBtn = Button::create("game/button_09.png","game/button-pressed_09.png");
        m_FourBtn->setScale9Enabled(true);
        m_FourBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_FourBtn,51);
        /** 五倍 */
        m_FiveBtn = Button::create("game/button_11.png","game/button-pressed_11.png");
        m_FiveBtn->setScale9Enabled(true);
        m_FiveBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_FiveBtn,51);
        
        m_OneBtn->setTag(TAG_MUL_ONE);
        m_TwoBtn->setTag(TAG_MUL_TWO);
        m_ThreeBtn->setTag(TAG_MUL_THERE);
        m_FourBtn->setTag(TAG_MUL_FOUR);
        m_FiveBtn->setTag(TAG_MUL_FIVE);
        
        float btnwidth=m_OneBtn->getContentSize().width;
        float height=Size.height *0.5 - 150;
        
        m_OneBtn->setPosition(Vec2(Size.width / 2-(btnwidth+10)*2, height));
        m_TwoBtn->setPosition(Vec2(Size.width / 2-(btnwidth+10), height));
        m_ThreeBtn->setPosition(Vec2(Size.width / 2, height));
        m_FourBtn->setPosition(Vec2(Size.width / 2+(btnwidth+10), height));
        m_FiveBtn->setPosition(Vec2(Size.width / 2+(btnwidth+10)*2, height));
        
        m_creatMulBtn=true;
    }
    else
    {
        m_OneBtn->setVisible(true);
        m_TwoBtn->setVisible(true);
        m_ThreeBtn->setVisible(true);
        m_FourBtn->setVisible(true);
        m_FiveBtn->setVisible(true);
    }
}

#pragma mark-选择倍数超时
void GamePlayScene::notChooseMulAction(float dt){
    m_OneBtn->setVisible(false);
    m_TwoBtn->setVisible(false);
    m_ThreeBtn->setVisible(false);
    m_FourBtn->setVisible(false);
    m_FiveBtn->setVisible(false);
    m_timeLayer->stopTimer();
    showCompare();
}

#pragma mark-显示结果
void GamePlayScene::showCompare(){
    m_player->showAllPokers();
    m_playerRight->showAllPokers();
    m_playerTopRight->showAllPokers();
    m_playerTopLeft->showAllPokers();
    m_playerLeft->showAllPokers();
    m_playNum++;
    if (m_playNum<=10) {
        auto delayTime = DelayTime::create(3.0);
        auto func=CallFunc::create(CC_CALLBACK_0(GamePlayScene::startNewPlay, this));
        auto seq=Sequence::create(delayTime,func, nullptr);
        this->runAction(seq);
    }
    
}

//#pragma mark-延迟执行重新开局
void GamePlayScene::startNewPlay(){
    char path[256] = { 0 };
    sprintf(path, "第%d局", m_playNum);
    m_pNoticeLabel->setString(path);
    m_player->emptyAllPokers();
    m_playerRight->emptyAllPokers();
    m_playerTopRight->emptyAllPokers();
    m_playerTopLeft->emptyAllPokers();
    m_playerLeft->emptyAllPokers();
    xiPai();
    m_iSendPk=0;
    m_iState = SendPokerState;
    schedule(schedule_selector(GamePlayScene::update));
}

