#include "Help.h"
#include "toolFunctions.h"
#include "MainScene.h"

USING_NS_CC;

Help::Help()
{
}


Help::~Help()
{
}

Scene* Help::scene(){
	Scene* scene = Scene::create();
	Help * help = Help::create();
	scene->addChild(help);
	return scene;
}

//初始化场景
bool Help::init()
{
	CCLayer::init();
	this->setTouchEnabled(true);		
	scheduleUpdate();
	if (!initBackground()) return false;
	if (!initButtons()) return false;
	if (!initNotice()) return false;
	if (!initInstruction()) return false;
	
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();		//添加触摸事件监听

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);									//设置单点触摸
	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->setSwallowTouches(true);														//设置可以触摸
	oneTouch->onTouchBegan = CC_CALLBACK_2(Help::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(Help::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(Help::onTouchEnded, this);
	oneTouch->onTouchCancelled = CC_CALLBACK_2(Help::onTouchCancelled, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(oneTouch, scrollView);			//触摸添加到滚动效

	//添加事件监听
	//scrollView->addEventListener(CC_CALLBACK_2(Help::onTouch, this));
	return true;
}

//void Help::onTouch(Ref* target, ScrollView::EventType eventType)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	int y = label->getPositionY();
//	CCLOG("offset=%d", y);
//	int offset = (int)y % 800;
//	// 调整位置
//
//	//switch (eventType)
//	//{
//	//	case ScrollView::EventType::SCROLL_TO_TOP:
//	//		if (y < 650)
//	//			label->setPositionY(y + 10);
//	//		break;
//	//}
//}

//初始化背景
bool Help::initBackground()
{
	CCSprite* bk = CCSprite::create("ui\\help.png");
	bk->setScale(2,1);
	if (!bk)
	{
		return false;
	}
	this->addChild(bk, 0);
	bk->setAnchorPoint(ccp(0, 0));						
	return true;
}

bool Help::initNotice()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	label_notice = Label::create("规则说明", "Arial", 30);
	//label_notice->setColor(Color3B::RED);
	label_notice->setTextColor(Color4B::RED);
	label_notice->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label_notice->getContentSize().height));
	this->addChild(label_notice, 1);
	return true;
}

bool Help::initInstruction()
{
	//获取主屏幕的尺寸
	auto visibleSize = Director::getInstance()->getVisibleSize();	//800,600
	CCDictionary* pDict = CCDictionary::createWithContentsOfFile("notice.xml");
	const char *charchinese = ((CCString*)pDict->objectForKey("name"))->getCString();
	label = Label::create(charchinese, "Arial", 25);
	label->setHorizontalAlignment(TextHAlignment::LEFT);
	label->setDimensions(800, 2000);
	label->setLineBreakWithoutSpace(true);
	label->setPosition(Vec2(10 + label->getContentSize().width / 2, 5 * (visibleSize.height / 6) + 120 - label->getContentSize().height / 2));

	//滚动条
	scrollView = Help::MyScrollView::create();
	scrollView->setContentSize(Size(500, 600));
	scrollView->setPosition(Vec2(0, 5 * (visibleSize.height / 6) + 420 - label->getContentSize().height / 2));
	scrollView->setTouchEnabled(true);
	scrollView->setInertiaScrollEnabled(true);
	scrollView->addChild(label, 0, 0);
	scrollView->setMinPos(5 * (visibleSize.height / 6) + 120 - label->getContentSize().height / 2);
	scrollView->setDirection(ScrollView::Direction::VERTICAL);
	this->addChild(scrollView);
	//scrollView->setScrollBarEnabled(true);
	//scrollView->setBounceEnabled(true);
	return true;
}

bool Help::initButtons()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Button* pBackBtn = Button::create("ui/reback.png");
	if (!pBackBtn) return false;
	pBackBtn->setScale(0.8, 0.8);
	pBackBtn->setTag(1);
	pBackBtn->setScale9Enabled(true);
	pBackBtn->setPosition(Vec2(40, 560));
	pBackBtn->addTouchEventListener(Help::onBtnTouch);
	this->addChild(pBackBtn, 1);
	return true;
}

//按钮点击事件回调
void Help::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	auto director = Director::getInstance();
	auto helpscene = Help::scene();
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case 1:
			//CCDirector::sharedDirector()->replaceScene(MainScene::scene());
			break;
		}
	}

}


void flushNoticeLabel(float delta)
{

}

bool Help::MyScrollView::onTouchBegan(Touch * touch, Event * unusedEvent){
	log("Help onTouchEnded");
	return true;
}


void Help::MyScrollView::onTouchMoved(Touch * touch, Event * unusedEvent){
	Size size = Director::getInstance()->getWinSize();
	//获取label当前位置
	auto y = this->getChildByTag(0)->getPositionY();				
	auto delte = touch->getDelta().y;

	if (delte < 0){              	//向下滑动
		if (y + delte > m_minPos)
			this->getChildByTag(0)->setPositionY(this->getChildByTag(0)->getPositionY() + touch->getDelta().y);
	}
	else               	//向上滑动
	{
		//滑动屏幕页数
		int screenCount = (this->getChildByTag(0)->getContentSize().height/2 )/ (size.height/2);	
		//滑动屏幕剩余位置差
		int screenDelta = int(this->getChildByTag(0)->getContentSize().height/2) % int(size.height/2);		
		int maxY = screenCount*size.height/2 - screenDelta;
		if (y + delte < maxY)
			this->getChildByTag(0)->setPositionY(this->getChildByTag(0)->getPositionY() + touch->getDelta().y);
	}
	CCLOG("offset1=%d", this->getChildByTag(0)->getPositionY() + touch->getDelta().y);
	CCLOG("offset2=%d", this->getChildByTag(0)->getPositionY());
	CCLOG("offset3=%d", touch->getDelta().y);
	log("Help onTouchesMoved");
}

void Help::MyScrollView::onTouchEnded(Touch * touch, Event * unusedEvent){
	/**
	auto pos1 = touch->getLocation();
	auto pos2 = touch->getLocationInView();
	auto pos3 = Director::getInstance()->convertToUI(pos2);
	auto pos4 = touch->getDelta();

	int y = this->getChildByTag(0)->getPositionY();
	this->getChildByTag(0)->setPositionY(y + pos4.y);
	CCLOG("offset=%d", y);
	*/
	//this->getChildByTag(0)->runAction(CCMoveTo::create(0, pos1));
	log("Help onTouchEnded");
}

void Help::MyScrollView::onTouchCancelled(Touch * touch, Event * unusedEvent){
	log("Help onTouchCancelled");
}