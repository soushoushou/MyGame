#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "constString.h"
#include "Global.h"
#include "NiuPoker.h"
#include "NiuPlayer.h"
USING_NS_CC;

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
    TAG_MUL_FIVE
};


GamePlayScene::GamePlayScene() :m_timeLayer(NULL), m_startGameBtn(NULL), m_bReady(false), m_isSend(true),
m_iSendPk(0), m_iState(StartState),m_btnSetting(NULL)

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
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_playerRight);
	CC_SAFE_DELETE(m_playerTopRight);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_DELETE(m_playerTopLeft);
	CC_SAFE_RELEASE(m_arrPokers);
	if (m_btnSetting)
	{
		delete m_btnSetting;
		m_btnSetting = NULL;
	}
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
        case StartState:
        {
		//µπº∆ ±
            if (server->isAllReady())
            {
                if (!m_timeLayer && m_bReady)
                {
                    m_timeLayer = TimeLayer::create();
                    addChild(m_timeLayer);
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
                notChooseMulAction();
                unschedule(schedule_selector(GamePlayScene::update));
            }
            break;
            
        }
	default:
		break;
	}
}

//≥ı ºªØ
bool GamePlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (!initBackground()) return false;
	if (!initButtons()) return false;
	srand((unsigned)time(NULL));//≥ı ºªØÀÊª˙÷÷◊”
	if (!initPlayer()) return false;
	if (!createPokers()) return false;
	if (!xiPai()) return false;
    schedule(schedule_selector(GamePlayScene::update));
	return true;
}

//≥ı ºªØ±≥æ∞
bool GamePlayScene::initBackground()
{
	auto size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ÃÌº”±≥æ∞
	auto spriteBK = Sprite::create("game/gamebg.png");
	spriteBK->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(spriteBK);
    
    m_pNoticeLabel = LabelTTF::create("第1局", "Arial", 50);
    if (!m_pNoticeLabel) return false;
    m_pNoticeLabel->setPosition(Vec2(size.width / 2,size.height / 2));
    m_pNoticeLabel->setColor(Color3B(255, 255, 255));
    this->addChild(m_pNoticeLabel);
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
	Size size = Director::getInstance()->getWinSize();
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

                //ƒ£ƒ‚µ±À˘”–ÕÊº“∂º◊º±∏∫√∫Û‘Ÿµπº∆ ±
                m_bReady = !m_bReady;
                DebugSimpleServer::getInstance()->playerReady("alw");
                break;
            }
            case TAG_NOT_HOG_BTN:
            {
                notHogBtnAction();
                break;
            }
            case TAG_HOG_BTN:
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
                notChooseMulAction();
                break;
            }
            default:
                break;
		}
	}
}

bool GamePlayScene::initPlayer(){
	Size size = Director::getInstance()->getVisibleSize();
	//…Ë÷√÷˜ÕÊº“µƒŒª÷√
    m_player->setPoint(Vec2(size.width / 2, size.height / 6-20));
    m_player->setPlayerClass(PlayerType_Me);
    //…Ë÷√ÕÊº“”“µƒŒª÷√
    m_playerRight->setPoint(Vec2(size.width - pkWidth_small * 3, size.height / 2));
    m_playerRight->setPlayerClass(PlayerType_Right);
    //…Ë÷√ÕÊº“…œ∂˛µƒŒª÷√
    m_playerTopRight->setPoint(Vec2(size.width*0.5 + pkWidth_small * 3, size.height / 6 * 5));
    m_playerTopRight->setPlayerClass(PlayerType_TopRight);
    //…Ë÷√ÕÊº“…œ“ªµƒŒª÷√
    m_playerTopLeft->setPoint(Vec2(size.width*0.5 - pkWidth_small * 4, size.height / 6 * 5));
    m_playerTopLeft->setPlayerClass(PlayerType_TopLeft);
    //…Ë÷√ÕÊº“◊ÛµƒŒª÷√
    m_playerLeft->setPoint(Vec2(65, size.height / 2));
    m_playerLeft->setPlayerClass(PlayerType_Left);

	return true;
}

NiuPoker* GamePlayScene::selectPoker(int huaSe, int num){
	NiuPoker* pk;
    char path[256] = { 0 };
    sprintf(path, "pokerBig/%d_%d@2x.png", huaSe,num);
    pk = NiuPoker::create("poker.png", Rect(0, 0, pkWidth_small, pkHeight_small));
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
		//¥¥Ω®52∏ˆ≈∆
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
#pragma mark-œ¥≈∆
bool GamePlayScene::xiPai(){
    Size size = Director::getInstance()->getVisibleSize();
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
        pk->setPosition(Vec2(size.width / 2, size.height / 2));
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
        auto size = Director::getInstance()->getVisibleSize();
        /** 不抢 */
        m_notHogBtn = Button::create("game/not_hog_button.png","game/not_hog_button_pressed.png");
        
        m_notHogBtn->setTag(TAG_NOT_HOG_BTN);
        
        m_notHogBtn->setScale9Enabled(true);
        
        m_notHogBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        
        this->addChild(m_notHogBtn);
        /** 抢庄 */
        m_HogBtn = Button::create("game/hog_button.png","game/hog_button_pressed.png");
        
        m_HogBtn->setTag(TAG_HOG_BTN);
        
        m_HogBtn->setScale9Enabled(true);
        
        m_HogBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        
        this->addChild(m_HogBtn);
        
        float btnwidth=m_notHogBtn->getContentSize().width;
        float height=size.height *0.5 - 150;
        m_notHogBtn->setPosition(Vec2(size.width / 2-(btnwidth*0.5+10), height));
        m_HogBtn->setPosition(Vec2(size.width / 2+(btnwidth*0.5+10), height));
        
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
        auto size = Director::getInstance()->getVisibleSize();
        /** 一倍 */
        m_OneBtn = Button::create("game/button_02.png","game/button-pressed_02.png");
        m_OneBtn->setScale9Enabled(true);
        m_OneBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_OneBtn);
        /** 二倍 */
        m_TwoBtn = Button::create("game/button_05.png","game/button-pressed_05.png");
        m_TwoBtn->setScale9Enabled(true);
        m_TwoBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_TwoBtn);
        /** 三倍 */
        m_ThreeBtn = Button::create("game/button_07.png","game/button-pressed_07.png");
        m_ThreeBtn->setScale9Enabled(true);
        m_ThreeBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_ThreeBtn);
        /** 四倍 */
        m_FourBtn = Button::create("game/button_09.png","game/button-pressed_09.png");
        m_FourBtn->setScale9Enabled(true);
        m_FourBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_FourBtn);
        /** 五倍 */
        m_FiveBtn = Button::create("game/button_11.png","game/button-pressed_11.png");
        m_FiveBtn->setScale9Enabled(true);
        m_FiveBtn->addTouchEventListener(CC_CALLBACK_2(GamePlayScene::onBtnTouch, this));
        this->addChild(m_FiveBtn);
        
        m_OneBtn->setTag(TAG_MUL_ONE);
        m_TwoBtn->setTag(TAG_MUL_TWO);
        m_ThreeBtn->setTag(TAG_MUL_THERE);
        m_FourBtn->setTag(TAG_MUL_FOUR);
        m_FiveBtn->setTag(TAG_MUL_FIVE);
        
        float btnwidth=m_OneBtn->getContentSize().width;
        float height=size.height *0.5 - 150;
        
        m_OneBtn->setPosition(Vec2(size.width / 2-(btnwidth+10)*2, height));
        m_TwoBtn->setPosition(Vec2(size.width / 2-(btnwidth+10), height));
        m_ThreeBtn->setPosition(Vec2(size.width / 2, height));
        m_FourBtn->setPosition(Vec2(size.width / 2+(btnwidth+10), height));
        m_FiveBtn->setPosition(Vec2(size.width / 2+(btnwidth+10)*2, height));
        
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
void GamePlayScene::notChooseMulAction(){
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

#pragma mark-延迟执行重新开局
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

