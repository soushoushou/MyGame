#include "TimeLayer.h"


TimeLayer::TimeLayer() :m_pFrameSprtie(NULL), m_bCanRemove(false)
{
    m_type=Tip_gameBegin;
}


TimeLayer::~TimeLayer()
{
}

Scene* TimeLayer::scene(){
	Scene* scene = Scene::create();
	TimeLayer *TimeLayer = TimeLayer::create();
	scene->addChild(TimeLayer);
	return scene;
}

//初始化
bool TimeLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}
//	if (m_pFrameSprtie)
//	{
//		this->addChild(m_pFrameSprtie);
//	}
    Size size = Director::getInstance()->getWinSize();
    m_pFrameSprtie = Sprite::create("tips/clockbg.png");
    m_pFrameSprtie->setPosition(Vec2(size.width / 2, size.height / 2 - 20));
    this->addChild(m_pFrameSprtie);
    
    m_tipSprite = Sprite::create("tips/tip_gameBegin.png");
    float height=m_pFrameSprtie->getPositionY()-((m_pFrameSprtie->getContentSize().height+m_tipSprite->getContentSize().height)*0.5+6);
    m_tipSprite->setPosition(Vec2(size.width / 2, height));
    this->addChild(m_tipSprite);
    
    setTime(5, 20, m_pFrameSprtie->getPosition());
    
    
	//吞噬touch消息
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *touch, Event *unused_event){return true; };
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


//设置消息框精灵
bool TimeLayer::setFrameSprite(const string fileName, const Vec2& pos)
{
	if (m_pFrameSprtie)
	{
		m_pFrameSprtie->initWithFile(fileName);
		m_pFrameSprtie->setPosition(pos);
	}
	else
	{
		m_pFrameSprtie = Sprite::create(fileName);
		if (!m_pFrameSprtie)
		{
			return false;
		}
		m_pFrameSprtie->setPosition(pos);
		this->addChild(m_pFrameSprtie);
	}
	return true;

}


TimeLayer* TimeLayer::createTimer(float time, float size, const Vec2& pos)
{
	TimeLayer* timeLayer = new TimeLayer;
	if (timeLayer && timeLayer->setTime(time, size, pos))
	{
		timeLayer->autorelease();
		return timeLayer;
	}
	else
	{
		delete timeLayer;
		timeLayer = NULL;
	}
	return NULL;
}

void TimeLayer::update(float delta)
{
	pTime -= delta;
	if (pTime > 0)
	{
		char* mtime = new char[10];
		//此处只是显示秒数  自己可以定义输出时间格式  
		sprintf(mtime, "%d", (int)pTime % 60);
		timeLabel->setString(mtime);
	}
	else
	{
		this->unschedule(schedule_selector(TimeLayer::update));
		m_bCanRemove = true;
	}
}

bool TimeLayer::canRemove() const
{
	return m_bCanRemove;
}

bool TimeLayer::setTime(float time, float size, const Vec2& pos)
{
	pTime = time;
	timeLabel = LabelTTF::create();
	timeLabel->setFontSize(size);
	timeLabel->setPosition(pos);

	this->addChild(timeLabel);

	schedule(schedule_selector(TimeLayer::update));

	return true;
}

void TimeLayer::changeType(TipType type){
    switch (type) {
        case Tip_gameBegin:
            m_tipSprite->setTexture("tips/tip_gameBegin.png");
            break;
        case Tip_hog:
            m_tipSprite->setTexture("tips/tip_hog.png");
            break;
        case Tip_chooseMul:
            m_tipSprite->setTexture("tips/tip_chooseMul.png");
            break;
        case Tip_waitOther:
            m_tipSprite->setTexture("tips/tip_waitOther.png");
            break;
        default:
            break;
    }
}

void TimeLayer::setNewTime(float time){
    pTime = time;
    m_bCanRemove=false;
    char* mtime = new char[10];
    sprintf(mtime, "%d", (int)pTime);
    timeLabel->setString("mtime");
    schedule(schedule_selector(TimeLayer::update));
}

void TimeLayer::setTimeAndType(float time, TipType type){
    setNewTime(time);
    changeType(type);
    this->setVisible(true);
}

void TimeLayer::stopTimer(){
    pTime=0;
    this->setVisible(false);
}

