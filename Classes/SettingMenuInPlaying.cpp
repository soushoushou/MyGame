#include "SettingMenuInPlaying.h"
#include "MainScene.h"
#include "PopupLayer.h"


SettingMenuInPlaying::SettingMenuInPlaying(Node* parent, unsigned long long playerID) :m_spFrame(NULL), m_spDropdownFrame(NULL), m_btnOptions(NULL),
m_btnDestoryRoom(NULL), m_btnQuitRoom(NULL), m_btnSetting(NULL), m_btnStatus(NORMAL), m_playerID(playerID)
{
	m_pParent = parent;
	init(parent);
}

SettingMenuInPlaying::SettingMenuInPlaying(Node* parent, Vec2 pos, unsigned long long playerID) :m_spFrame(NULL), m_spDropdownFrame(NULL), m_btnOptions(NULL),
m_btnDestoryRoom(NULL), m_btnQuitRoom(NULL), m_btnSetting(NULL), m_btnStatus(NORMAL), m_playerID(playerID)
{
	m_pParent = parent;
	init(parent);
	setPos(pos);
}

SettingMenuInPlaying::~SettingMenuInPlaying()
{
	m_spFrame->removeAllChildren();
	m_spFrame->release();
}

void SettingMenuInPlaying::setPos(Vec2 pos)
{
	if (m_spFrame)
	{
		m_spFrame->setPosition(pos);
	}
}

bool SettingMenuInPlaying::init(Node* parent)
{
	if (!parent)
	{
		return false;
	}
	if(!m_spFrame)
	{
		m_spFrame = Sprite::create("game/settingFrame.png");
		if (!m_spFrame)
		{
			return false;
		}
	}
	if (!m_btnOptions)
	{
		m_btnOptions = Button::create("game/options_normal.png", "game/options_pressed.png");
		if (!m_btnOptions)
		{
			return false;
		}
		m_btnOptions->setAnchorPoint(Vec2(0.5, 0.5));
		m_btnOptions->setPosition(Vec2(73,25));
		m_spFrame->addChild(m_btnOptions);
		m_btnOptions->addTouchEventListener(CC_CALLBACK_2(SettingMenuInPlaying::onOptionsTouch, this));

	}
	parent->addChild(m_spFrame,1000);
	return true;
}

void SettingMenuInPlaying::onBtnsTouch(Ref* pSender, Widget::TouchEventType evnet)
{
	if (evnet == Widget::TouchEventType::ENDED && m_btnStatus == EXPAND)
	{
		Button* pBtn = dynamic_cast<Button*>(pSender);
		if (pBtn == m_btnSetting)
		{
			CCSize size = CCDirector::sharedDirector()->getWinSize();
			PopupLayer* pl = PopupLayer::settingDialog("popuplayer/settingbg.png", Size(size.width / 2, size.height / 7 * 4));
			m_pParent->addChild(pl,999);
		}
		else if (pBtn == m_btnQuitRoom)
		{
			auto dialog = PopupLayer::backDialog("popuplayer/backbg.png", Size(610, 399), "quit room", "Are you sure?");
			m_pParent->addChild(dialog,999);
			dialog->setCallbackFunc(this, callfuncN_selector(SettingMenuInPlaying::quitRoomCallback));
		}
		else if (pBtn == m_btnDestoryRoom)
		{
			log("3333");
		}
	}
}

void SettingMenuInPlaying::quitRoomCallback(Node* node)
{
	auto s = MainScene::scene(m_playerID);
	if (s)
		Director::getInstance()->replaceScene(s);
}

void SettingMenuInPlaying::onOptionsTouch(Ref* pSender, Widget::TouchEventType evnet)
{
	if (evnet == Widget::TouchEventType::ENDED)
	{
		Button* pBtn = dynamic_cast<Button*>(pSender);
		if (pBtn == m_btnOptions)
		{
			if (m_btnStatus == NORMAL)
			{
				m_spDropdownFrame = Sprite::create("game/dropdownFrame.png");
				m_spDropdownFrame->setPosition(Vec2(70,-120));
				m_spFrame->addChild(m_spDropdownFrame,-1);
				m_btnSetting = Button::create("game/setting_normal.png", "game/seeting_pressed.png");
				m_btnQuitRoom = Button::create("game/quitRoom_normal.png", "game/quitRoom_pressed.png");
				m_btnDestoryRoom = Button::create("game/destoryRoom_normal.png", "game/destoryRoom_pressed.png");
				m_btnSetting->setPosition(Vec2(m_spDropdownFrame->getContentSize().width / 2, 230));
				m_btnQuitRoom->setPosition(Vec2(m_spDropdownFrame->getContentSize().width / 2, 160));
				m_btnDestoryRoom->setPosition(Vec2(m_spDropdownFrame->getContentSize().width / 2, 80));
				m_spDropdownFrame->addChild(m_btnSetting);
				m_spDropdownFrame->addChild(m_btnQuitRoom);
				m_spDropdownFrame->addChild(m_btnDestoryRoom);
				m_btnSetting->addTouchEventListener(CC_CALLBACK_2(SettingMenuInPlaying::onBtnsTouch, this));
				m_btnQuitRoom->addTouchEventListener(CC_CALLBACK_2(SettingMenuInPlaying::onBtnsTouch, this));
				m_btnDestoryRoom->addTouchEventListener(CC_CALLBACK_2(SettingMenuInPlaying::onBtnsTouch, this));
				m_btnStatus = EXPAND;
			}
			else if (m_btnStatus == EXPAND)
			{
				m_btnStatus = NORMAL;
				m_spFrame->removeChild(m_spDropdownFrame,true);
			}
		}
	}
}