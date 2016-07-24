#include "TimeLayer.h"


TimeLayer::TimeLayer() :m_pFrameSprtie(NULL)
{
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
	if (m_pFrameSprtie)
	{
		this->addChild(m_pFrameSprtie);
	}

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
	if (pTime >= 0)
	{
		char* mtime = new char[10];
		//此处只是显示秒数  自己可以定义输出时间格式  
		sprintf(mtime, "%d", (int)pTime % 60);
		timeLabel->setString(mtime);
	}
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