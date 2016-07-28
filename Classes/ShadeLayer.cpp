#include "ShadeLayer.h"


ShadeLayer::ShadeLayer() :m_pFrameSprtie(NULL), m_plblTitle(NULL), m_plblContent(NULL)
{
}


ShadeLayer::~ShadeLayer()
{
}

Scene* ShadeLayer::scene(){
	Scene* scene = Scene::create();
	ShadeLayer *shadeLayer  = ShadeLayer::create();
	scene->addChild(shadeLayer);
	return scene;
}

//初始化
bool ShadeLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0,0,0,100)))
	{
		return false;
	}
	if (m_pFrameSprtie)
	{
		this->addChild(m_pFrameSprtie);
	}
	if (m_plblContent)
	{
		this->addChild(m_plblContent);
	}
	if (m_plblTitle)
	{
		this->addChild(m_plblTitle);
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
bool ShadeLayer::setFrameSprite(const string fileName, const Vec2& pos)
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

bool ShadeLayer::setTitle(const string title, const string fontName, float size, const Vec2& pos)
{
	if (m_plblTitle)
	{
		m_plblTitle->setString(title);
		m_plblTitle->setFontName(fontName);
		m_plblTitle->setFontSize(size);
		m_plblTitle->setPosition(pos);
	}
	else
	{
		m_plblTitle = LabelTTF::create(title, fontName, size);
		if (!m_plblTitle)
		{
			return false;
		}
		m_plblTitle->setPosition(pos);
		this->addChild(m_plblTitle);
	}
	return true;
}

bool ShadeLayer::setContent(const string content, const string fontName, float size, const Vec2& pos)
{
	if (m_plblContent)
	{
		m_plblContent->setString(content);
		m_plblContent->setFontName(fontName);
		m_plblContent->setFontSize(size);
		m_plblContent->setPosition(pos);
	}
	else
	{
		m_plblContent = LabelTTF::create(content, fontName, size);
		if (!m_plblContent)
		{
			return false;
		}
		m_plblContent->setPosition(pos);
		this->addChild(m_plblContent);
	}
	return true;
}