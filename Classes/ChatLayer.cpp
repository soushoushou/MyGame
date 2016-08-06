#include "ChatLayer.h"

using namespace ui;

#define TAG_SEND_BTN	3
#define TAG_CLOSE_BTN	4

ChatLayer::ChatLayer() :m_pFrameSprtie(NULL)
{
}


ChatLayer::~ChatLayer()
{
}

Scene* ChatLayer::scene(){
	Scene* scene = Scene::create();
	ChatLayer *chatLayer = ChatLayer::create();
	scene->addChild(chatLayer);
	return scene;
}

//初始化
bool ChatLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}

	if (m_pFrameSprtie)
	{
		this->addChild(m_pFrameSprtie);
	}
	
	if (!initChatBG())
	{
		return false;
	}

	if (!initTitle())
	{
		return false;
	}
	if (!initButton())
	{
		return false;
	}
	if (!initEditBox())
	{
		return false;
	}

	//吞噬touch消息
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *touch, Event *unused_event){return true; };
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//初始化背景
bool ChatLayer::initChatBG()
{
	auto size = Director::getInstance()->getWinSize();
	if (m_pFrameSprtie)
	{
		m_pFrameSprtie->initWithFile("game/chat_bg.png");
		m_pFrameSprtie->setPosition(Vec2(size.width / 2, size.height / 2));
	}
	else
	{
		m_pFrameSprtie = Sprite::create("game/chat_bg.png");
		if (!m_pFrameSprtie)
		{
			return false;
		}
		m_pFrameSprtie->setPosition(Vec2(size.width / 2, size.height / 2));
		this->addChild(m_pFrameSprtie);
	}
	return true;
}

bool ChatLayer::initTitle()
{
	auto size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("game/chat_title.png");
	sprite->setPosition(Vec2(size.width / 2, size.height / 2 + 212));
	this->addChild(sprite);
	return true;
}

bool ChatLayer::initButton()
{
	auto size = Director::getInstance()->getWinSize();
	//发送按钮
	Button* sendButton = Button::create("game/chat_send.png");
	sendButton->setTag(TAG_SEND_BTN);
	sendButton->setScale9Enabled(true);
	sendButton->setPosition(Vec2(size.width / 2 + 250, size.height / 2 - 180));
	sendButton->addTouchEventListener(CC_CALLBACK_2(ChatLayer::onBtnTouch, this));
	this->addChild(sendButton);

	//关闭按钮
	Button* closeButton = Button::create("game/close.png");
	closeButton->setTag(TAG_CLOSE_BTN);
	closeButton->setScale9Enabled(true);
	closeButton->setPosition(Vec2(size.width / 2 + 340, size.height / 2 + 215));
	closeButton->addTouchEventListener(CC_CALLBACK_2(ChatLayer::onBtnTouch, this));
	this->addChild(closeButton);

	return true;
}

//初始化编辑框
bool ChatLayer::initEditBox()
{
	auto size = Director::getInstance()->getWinSize();
	EditBox* chatEditBox = EditBox::create(CCSizeMake(493, 87), Scale9Sprite::create("game/chat_editBox.png"));
	chatEditBox->setPosition(Vec2(size.width / 2 - 80, size.height / 2 - 180));
	chatEditBox->setFontColor(Color3B(0, 0, 0));//设置字体颜色
	chatEditBox->setFontSize(30);
	chatEditBox->setPlaceHolder("");//设置预置文本    
	chatEditBox->setMaxLength(8);//设置最大长度    
	chatEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行   
	chatEditBox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位    
	chatEditBox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型    
	//chatEditBox->setDelegate(this);//当前类继承CCEditBoxDelegate类    
	chatEditBox->setTag(101);
	this->addChild(chatEditBox);

	return true;
}

bool ChatLayer::createListView(const vector<pair<string, string>> quickMessage)
{
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	lv = ListView::create();
	lv->setDirection(ui::ScrollView::Direction::VERTICAL);	//设置为垂直方向
	lv->setBounceEnabled(true);
	lv->setTouchEnabled(true);
	//lv->setBackGroundImage("game/chat_bg.png");
	lv->setBackGroundImageScale9Enabled(true);
	lv->setContentSize(Size(700, 300));
	lv->setAnchorPoint(Point(0.5, 0.5));
	lv->setPosition(Point(size.width / 2, size.height / 2));
	lv->addEventListenerListView(this, listvieweventselector(ChatLayer::selectedItemEvent));
	this->addChild(lv);

	for (int i = 0; i < quickMessage.size(); ++i)
	{
		auto button = Button::create("game/chat-line.png");
		button->setPosition(Point(size.width / 2 - 220, size.height / 2 - 270));
		button->setScale9Enabled(true);
		button->setName(quickMessage[i].second);
		button->addTouchEventListener(CC_CALLBACK_2(ChatLayer::onBtnTouch, this));

		LabelTTF* quickLable = LabelTTF::create(quickMessage[i].first, "fonts/arial.ttf", 30);
		//quickLable->setPosition(Director::getInstance()->convertToUI(Vec2(quickLable->getContentSize().width / 2 + 70, quickLable->getContentSize().height / 2 + 590)));
		quickLable->setPosition(Point(size.width / 2 - 350, size.height / 2 - 285));
		button->addChild(quickLable);

		//item的布局
		auto layout = Layout::create();
		layout->setBackGroundImageScale9Enabled(true);
		layout->setTouchEnabled(true);
		layout->setContentSize(Size(650, 70));

		layout->addChild(button);	
		lv->pushBackCustomItem(layout);
	}
	lv->setItemsMargin(10);

	return true;
}

void ChatLayer::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Size size = Director::sharedDirector()->getWinSize();
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* button = (Button*)pSender;
		unsigned int tag = button->getTag();
		switch (tag)
		{
		case TAG_SEND_BTN:
		{
			log("send chat");
			
			break;
		}
		case TAG_CLOSE_BTN:
		{
			log("close chat");
			this->removeFromParent();
			break;
		}
		default:
		{
			log("quick chat");	
			SimpleAudioEngine::getInstance()->playEffect(button->getName().c_str());
			this->removeFromParent();
			break;
		}
		}
	}
}

void ChatLayer::selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type)
{
	switch (type) {
	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		break;
	}
	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		break;
	}	
	default:
		break;
	}
}

void ChatLayer::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void ChatLayer::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void ChatLayer::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void ChatLayer::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
}