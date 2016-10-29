#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "constString.h"
#include "Global.h"
#include "NiuPoker.h"
#include "NiuPlayer.h"
#include "MainScene.h"
//#include "direct.h"
#include <fstream>
#include "AudioManager.h"
using namespace std;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "CDMRecordObject.h"
#endif

USING_NS_CC;

bool isRecording;

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


GamePlayScene::GamePlayScene(unsigned long long playerID, int roomID) :m_timeLayer(NULL), m_startGameBtn(NULL), m_bReady(false),
m_iState(StartState), m_btnSetting(NULL), m_playerID(playerID), m_roomID(roomID), m_pSiteManager(nullptr), m_bGameStart(false)
{
    m_creatHogBtn=false;
    m_creatMulBtn=false;
    m_playNum=1;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    m_recordObject=new CDMRecordObject();
//#endif
    

}

GamePlayScene::~GamePlayScene(){
	DebugSimpleServer::getInstance()->quitRoom("alw");
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
	NetworkManger *pNet = NetworkManger::getInstance();
	if (!pNet->ackQueueIsEmpty())
	{
		unsigned short cmd = pNet->getQueueFrontACKCmd();
		switch (cmd)
		{
			case PP_DOUNIU_GET_ROLEINFO_ACK:
			{
				log("info ack uc");
				S_GetPlayerInfoACK s = S_GetPlayerInfoACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				m_pSiteManager->joinSite(m_playerID, s.m_strPlayerName, s.m_currentDiamond, s.m_currentMoney);
				m_testID.push_back(s.m_playerID);
			}
			break;
			case PP_DOUNIU_VOICE_CHAT_ACK:
			{
				log("voice ack uc");
				S_VoiceChatACK s = S_VoiceChatACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                AudioManager::getInstance()->binaryConvertedToFile_Rev(m_recordObject->destPath, s.m_voiceBuf, s.m_voiceSize);
                m_recordObject->StartPlay();
#endif
                
                log(s.m_packageLen);
				
			}
			break;	
			case PP_DOUNIU_QIANGZHUANG_ACK:
			{
				S_QiangZhuangACK ack = S_QiangZhuangACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				if (ack.m_statusCode == 0)
				{
					m_pSiteManager->showZhuangJia(ack.m_ZhuangJiaID);
					log("qiang zhuang success!");
				}
				else
					log("qiang zhuang failed!");
				
			}
			break;
			case PP_DOUNIU_QUIT_ROOM_ACK:
			{
				log("quit room ack");
				S_QuitRoomACK ack = S_QuitRoomACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				if (ack.m_isOK == 0)
				{
					if (m_playerID == ack.m_playerID)
					{
						auto s = MainScene::scene(m_playerID);
						if (s)
						{
							Director::getInstance()->replaceScene(s);
						}
					}
					else
					{
						m_pSiteManager->leaveSite(ack.m_playerID);
					}
				}
				else
				{
					log("quit room but failed!");
				}
			}
			break;
			case PP_DOUNIU_YAZHU_ACK:
			{
				S_YaZhuACK ack = S_YaZhuACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				if (ack.m_isOK == 0)
				{
					log("ya zhu success!");
					S_TanPaiReq t;
					NetworkManger::getInstance()->SendRequest_TanPai(t);
					m_OneBtn->setVisible(false);
					m_TwoBtn->setVisible(false);
					m_ThreeBtn->setVisible(false);
					m_FourBtn->setVisible(false);
					m_FiveBtn->setVisible(false);
					m_timeLayer->stopTimer();
				}
				else
					log("ya zhu failed!");

			}
			break;
			case PP_DOUNIU_MEMBER_INFO_ACK:
			{
				S_GetMemberInfoACK ack = S_GetMemberInfoACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				m_pSiteManager->joinSite(ack.m_playerID, ack.m_strPlayerName, ack.m_currentDiamond, ack.m_currentMoney);
			}
			break;
			case PP_DOUNIU_READY_ACK:
			{
				S_ReadyPlayACK ack = S_ReadyPlayACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				if (ack.m_isOK == 0)
				{
					log("ready successed!");
					/*char buf[100] = { 0 };
					sprintf(buf, "ready player id = %d", ack.m_playerID);
					log(buf);*/
				}
				else
					log("ready failed!");
			}
			break;
			case PP_DOUNIU_GAME_START_ACK:
			{
				S_GameStartACK ack = S_GameStartACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				m_bGameStart = true;
	
			}
			break;
			case PP_DOUNIU_FAPAI_ACK:
			{
				S_FaPaiACK ack = S_FaPaiACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				log("fapai");
				//发牌
				vector<S_PlayerPorker> porkers;
				for (int i = 0; i < ack.m_playerID.size(); ++i)
				{
					S_PlayerPorker s;
					s.playerID = ack.m_playerID[i];
					for (int j = 0; j < 5; ++j)
					{
						s.vecPorkerIndex[j] = ack.m_pokers[(i)* 5 + j]-1;
					}
					porkers.push_back(s);
				}
				m_pPorkerManager->SendPorker(porkers);
				m_iState = SendPokerState;
				break;
			}
			case PP_DOUNIU_TANPAI_ACK:
			{
				S_TanPaiACK ack = S_TanPaiACK::convertDataFromBinaryData(pNet->getQueueFrontACKBinaryData());
				pNet->popACKQueue();
				showCompare();
			}
			break;
			default:
			break;
		}
	}


	switch (m_iState)
	{
        case StartState:
        {
			/////暂时测试用
			//static bool flag = true;
			//static int ccc = 2;
			//static int bbb = 22;
			//char buf[10] = { 0 };
			//sprintf(buf, "%d", bbb);
			//string name = buf;
			//if (rand()%100<50 && flag && m_testID.size()<5)
			//{
			//	m_pSiteManager->joinSite(ccc, name, rand() % 1000, rand() % 10000);
			//	m_testID.push_back(ccc);
			//	if (rand() % 3 == 1)
			//	{
			//		static int iii = 2;
			//		m_pSiteManager->leaveSite(iii);
			//		for (vector<unsigned long long>::iterator iter = m_testID.begin(); iter != m_testID.end(); ++iter)
			//		{
			//			if (*iter == iii)
			//			{
			//				m_testID.erase(iter);
			//				break;
			//			}
			//		}
			//		++iii;
			//	}
			//	++ccc;
			//	++bbb;
			//}
			//if (m_testID.size()==5)
			//{
			//	if (!m_timeLayer && m_bReady)
			//	{
			//		m_timeLayer = TimeLayer::create();
			//		addChild(m_timeLayer, 50);
			//	}
			//	if (m_timeLayer && m_timeLayer->canRemove())
			//	{
			//		m_timeLayer->setVisible(false);
			//		m_startGameBtn->setVisible(false);
			//		m_iState = SendPokerState;

			//		//发牌
			//		vector<S_PlayerPorker> porkers;
			//		vector<int> ttt(52, 0);
			//		for (int i = 0; i < 52; ++i)
			//		{
			//			ttt[i] = i+1;
			//		}
			//		for (int i = 0; i < 25; ++i)
			//		{
			//			int t = rand() % 52;
			//			int c = ttt[t];
			//			ttt[t] = ttt[i];
			//			ttt[i] = c;
			//		}
			//		for (int i = 0; i < m_testID.size(); ++i)
			//		{
			//			S_PlayerPorker s;
			//			s.playerID = m_testID[i];
			//			for (int j = 0; j < 5; ++j)
			//			{
			//				s.vecPorkerIndex[j] = ttt[(i)* 5 + j]-1;
			//			}
			//			porkers.push_back(s);
			//		}
			//		m_pPorkerManager->SendPorker(porkers);
			//	}
			//	flag = false;
			//}
			////////////////////////////////////////////////////////////////////////////
			if (m_bGameStart)
			{
				if (!m_timeLayer && m_bReady)
				{
					m_timeLayer = TimeLayer::create();
					addChild(m_timeLayer, 50);
				}
				if (m_timeLayer && m_timeLayer->canRemove())
				{
					m_timeLayer->setVisible(false);
					m_startGameBtn->setVisible(false);
					S_FaPaiReq s;
					NetworkManger::getInstance()->SendRequest_FaPai(s);
					m_bGameStart = false;
				}
			}
            break;
        }
		case SendPokerState:
			{
				if (m_pPorkerManager->RunActions())
				{
					m_iState = HogState;
					showHogButton();
				}
			}
            break;
        case HogState:{
            if (m_timeLayer && m_timeLayer->canRemove())
            {
                notHogBtnAction();
                //unschedule(schedule_selector(GamePlayScene::update));
            }
            break;
        }
        case ChooseMultipleState:{
            if (m_timeLayer && m_timeLayer->canRemove())
            {
                notChooseMulAction(0);
                //unschedule(schedule_selector(GamePlayScene::update));
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
	srand((unsigned)time(NULL));//初始化随机种子

    schedule(schedule_selector(GamePlayScene::update));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    isRecording=false;
    m_recordObject=new CDMRecordObject();
#endif
	m_pSiteManager = new SiteManager(this,m_playerID);
	m_pPorkerManager = new PorkerManager(this, m_pSiteManager);

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
	m_pRoomNumberLabel->setColor(Color3B(220, 190, 59));
    this->addChild(m_pRoomNumberLabel);
    
    m_pNoticeLabel = LabelTTF::create("第1局", "Arial", 25);
    if (!m_pNoticeLabel) return false;
    m_pNoticeLabel->setPosition(Vec2(size.width / 2,size.height / 2 + 290));
	m_pNoticeLabel->setColor(Color3B(220, 190, 59));
    this->addChild(m_pNoticeLabel);
    
    m_pModelLabel = LabelTTF::create("模式:抢庄模式", "Arial", 25);
    if (!m_pModelLabel) return false;
    m_pModelLabel->setPosition(Vec2(size.width / 2 + 270, size.height / 2 + 290));
	m_pModelLabel->setColor(Color3B(220, 190, 59));
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
	m_btnSetting = new SettingMenuInPlaying(this,Director::getInstance()->convertToUI(Vec2(980 + 68.5, 22)),m_playerID);
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
	S_GetPlayerInfoReq fp(m_playerID);
	NetworkManger::getInstance()->SendRequest_GetPlayerInfo(fp);
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
					bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/video/android/Audio", "recordAudio", "()Ljava/lang/String;");

					jobject jobj;
					if (!isHave) {
						CCLog("jni:此函数不存在");
					}else{
						CCLog("jni:此函数存在");
						//调用此函数
						jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,823);
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
				//showWinDialog();
				button->setTouchEnabled(false);
				button->loadTextures("game/startgamePressed.png", "");
				//模拟当所有玩家都准备好后再倒计时
				m_bReady =!m_bReady;
				S_ReadyPlayReq req;
				NetworkManger::getInstance()->SendRequest_ReadyPlay(req);
                break;
            }
            case TAG_HOG_BTN:			//抢庒
            {
				m_notHogBtn->setVisible(false);
				m_HogBtn->setVisible(false);
				m_timeLayer->stopTimer();
				m_iState = CompareState;
				S_QiangZhuangReq s;
				NetworkManger::getInstance()->SendRequest_QiangZhuang(s);
				int beishu = rand() % 5 + 1;
				S_YaZhuReq t(beishu);
				NetworkManger::getInstance()->SendRequest_YaZhu(t);
                //notHogBtnAction();
                break;
            }
            case TAG_NOT_HOG_BTN:		//不抢庒
            {
                m_notHogBtn->setVisible(false);
                m_HogBtn->setVisible(false);
                m_timeLayer->stopTimer();
                m_iState=ChooseMultipleState;
                showChooseMultipleButton();
                break;
            }
			case TAG_MUL_ONE:
			{
				S_YaZhuReq s(1);
				NetworkManger::getInstance()->SendRequest_YaZhu(s);
			}
				break;
			case TAG_MUL_TWO:
			{
				S_YaZhuReq s(2);
				NetworkManger::getInstance()->SendRequest_YaZhu(s);
			}
				break;
			case TAG_MUL_THERE:
			{
				S_YaZhuReq s(3);
				NetworkManger::getInstance()->SendRequest_YaZhu(s);
			}
				break;
			case TAG_MUL_FOUR:
			{
				S_YaZhuReq s(4);
				NetworkManger::getInstance()->SendRequest_YaZhu(s);
			}
				break;
			case TAG_MUL_FIVE:
			{
				S_YaZhuReq s(5);
				NetworkManger::getInstance()->SendRequest_YaZhu(s);
			}
                //notChooseMulAction(0);
//                m_player->showMulti(tag-TAG_MUL_ONE+1,this);
//                scheduleOnce(schedule_selector(GamePlayScene::notChooseMulAction), 10.0f);
                break;
			case TAG_CHAT_BTN:
			{


				log("chat");
				auto Size = Director::getInstance()->getWinSize();
				m_chatLayer = ChatLayer::create();

				//快捷聊天内容以及音乐地址
				vector<pair<string, string>> quickMessage;
				quickMessage.push_back(pair<string, string>("1a", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("2aa", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("3aa", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("4aaa", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("5aaaa", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("6aaaaa", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("7bb", "game/message1.mp3"));
				quickMessage.push_back(pair<string, string>("8bbb", "game/message1.mp3"));



				//m_chatLayer->createListView(quickMessage);
				m_chatLayer->readMessage(quickMessage);
				m_chatLayer->createListView();

				addChild(m_chatLayer,500);
				break;
			}
            case TAG_RECORD_BTN:{
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                log("发送");
                if (m_recordObject->convertToMp3()) {
                    AudioManager::getInstance()->fileConvertedToBinary_Send(m_recordObject->path);
                }
				#endif
				#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
					JniMethodInfo minfo;//定义Jni函数信息结构体
					//getStaticMethodInfo 次函数返回一个bool值表示是否找到此函数
					bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/video/android/Audio", "startPlay", "()Ljava/lang/String;");

					jobject jobj;

					if (!isHave) {
						CCLog("jni:此函数不存在");
					}else{
						CCLog("jni:此函数存在");
						//调用此函数
						jstring js_pkn = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID,823);
						std::string str_pkn = JniHelper::jstring2string(js_pkn);  
						fstream _file;
						_file.open(str_pkn, ios::in);
						if (!_file)
						{
							log("video file notin");
						}
						else
						{
							//Load_File_SEND(str_pkn.data());
							AudioManager::getInstance()->fileConvertedToBinary_Send(str_pkn.data());
							log("video file in");
						}
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


void GamePlayScene::menuCloseCallback(Ref* pSender)
{
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
	int beishu = rand() % 5 + 1;
	S_YaZhuReq s(beishu);
	NetworkManger::getInstance()->SendRequest_YaZhu(s);
	m_iState = CompareState;
    //m_iState=CompareState;
	//S_TanPaiReq s;
	//NetworkManger::getInstance()->SendRequest_TanPai(s);
	//showCompare();
}
void GamePlayScene::showWinDialog() {
	PopupLayer* pl = PopupLayer::wlDialog("popuplayer/win.png", Size(600, 600));
	vector<pair<int, int>> quickMessage;
	quickMessage.push_back(pair<int, int>(1, +1200));
	quickMessage.push_back(pair<int, int>(2, -1200));
	quickMessage.push_back(pair<int, int>(3, 0));
	quickMessage.push_back(pair<int, int>(4, 2400));
	quickMessage.push_back(pair<int, int>(5, -1200));
	pl->createWLListView(quickMessage);
	this->addChild(pl,100);
}
void GamePlayScene::showLoseDialog() {
	PopupLayer* pl = PopupLayer::recordDialog("popuplayer/lose.png", Size(600, 600));
	vector<pair<int, int>> quickMessage;
	quickMessage.push_back(pair<int, int>(1, +1200));
	quickMessage.push_back(pair<int, int>(2, -1200));
	quickMessage.push_back(pair<int, int>(3, 0));
	quickMessage.push_back(pair<int, int>(4, 2400));
	quickMessage.push_back(pair<int, int>(5, -1200));
	pl->createWLListView(quickMessage);
	this->addChild(pl);
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
	int beishu = rand() % 5 + 1;
	S_YaZhuReq s(beishu);
	NetworkManger::getInstance()->SendRequest_YaZhu(s);
	m_iState = CompareState;
	//S_TanPaiReq s;
	//NetworkManger::getInstance()->SendRequest_TanPai(s);
	//showCompare();
}

#pragma mark-显示结果
void GamePlayScene::showCompare(){
	m_pPorkerManager->ShowAllPorkers();
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
	m_pPorkerManager->EmptyAllPorkers();
	S_FaPaiReq s;
	NetworkManger::getInstance()->SendRequest_FaPai(s);
}

