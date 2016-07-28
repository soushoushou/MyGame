#include "UserProfileUI.h"
#include "PopupLayer.h"
UserProfileUI::UserProfileUI(Node* pParent)
{
	m_strPlayerName = "";
	m_nDiamond = 0;
	m_lblDiamond = NULL;
	m_spHead = NULL;
	m_lblPlayerName = NULL;
	m_pParent = pParent;
	m_spFrame = NULL;
	m_spDianmond = NULL;
}


UserProfileUI::~UserProfileUI()
{
}


HerizelUserProfileUI::HerizelUserProfileUI(Node* pParent) :UserProfileUI(pParent)
{

}

HerizelUserProfileUI::HerizelUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond):
UserProfileUI(pParent)
{
	auto director = Director::getInstance();
	m_spFrame = Sprite::create("MainScene/userProfileFrame.png");
	pParent->addChild(m_spFrame);
	m_spFrame->setPosition(director->convertToUI(pos));
	m_spHead = Sprite::create(headFileName);
	m_spHead->setPosition(Vec2(55, 55));
	m_spFrame->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(Vec2(110,90));
	m_spFrame->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(Vec2(105, 55));
	m_spFrame->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(Vec2(165, 45));
	m_spFrame->addChild(m_lblDiamond);
}

bool HerizelUserProfileUI::setProfile(Vec2 pos, const string headFileName, const string name, const int diamond)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	m_spFrame = Sprite::create("MainScene/userProfileFrame.png");
	if (!m_spFrame)
	{
		return false;
	}
	m_pParent->addChild(m_spFrame);
	m_spFrame->setPosition(director->convertToUI(pos));
	if (!m_spFrame)
	{
		return false;
	}
	m_spHead = Sprite::create(headFileName);
	if (!m_spHead)
	{
		return false;
	}
	m_spHead->setPosition(Vec2(55, 55));
	m_spFrame->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
	if (!m_lblPlayerName)
	{
		return false;
	}
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(Vec2(110, 90));
	m_spFrame->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	if (!m_spDianmond)
	{
		return false;
	}
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(Vec2(105, 55));
	m_spFrame->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	if (!m_lblDiamond)
	{
		return false;
	}
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(Vec2(165, 45));
	m_spFrame->addChild(m_lblDiamond);
	return true;
}

VerticalUserProfileUI::VerticalUserProfileUI(Node* pParent) :UserProfileUI(pParent)
{

}

VerticalUserProfileUI::VerticalUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond):
UserProfileUI(pParent)
{
	auto director = Director::getInstance();
	m_spFrame = Sprite::create("MainScene/userProfileFrameV.png");
	pParent->addChild(m_spFrame);
	m_spFrame->setPosition(director->convertToUI(pos));
	m_spHead = Sprite::create(headFileName);
	m_spHead->setPosition(Vec2(62, 120));
	m_spFrame->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
	m_lblPlayerName->setPosition(Vec2(m_spFrame->getContentSize().width / 2, 60));
	m_spFrame->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(Vec2(5, 45));
	m_spFrame->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 20);
	m_lblDiamond->setColor(Color3B(255, 252, 0));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(Vec2(55, 35));
	m_spFrame->addChild(m_lblDiamond);
}

bool VerticalUserProfileUI::setProfile(Vec2 pos, const string headFileName, const string name, const int diamond)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	m_spFrame = Sprite::create("MainScene/userProfileFrameV.png");
	if (!m_spFrame)
	{
		return false;
	}
	m_pParent->addChild(m_spFrame);
	m_spFrame->setPosition(director->convertToUI(pos));
	m_spHead = Sprite::create(headFileName);
	if (!m_spHead)
	{
		return false;
	}
	m_spHead->setPosition(Vec2(62, 120));
	m_spFrame->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
	if (!m_lblPlayerName)
	{
		return false;
	}
	m_lblPlayerName->setPosition(Vec2(m_spFrame->getContentSize().width / 2, 60));
	m_spFrame->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	if (!m_spDianmond)
	{
		return false;
	}
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(Vec2(5, 45));
	m_spFrame->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 20);
	if (!m_lblDiamond)
	{
		return false;
	}
	m_lblDiamond->setColor(Color3B(255, 252, 0));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(Vec2(55, 35));
	m_spFrame->addChild(m_lblDiamond);
	return true;
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond) :
HerizelUserProfileUI(pParent)
{
	auto director = Director::getInstance();
	m_spRoundRect = Sprite::create("MainScene/roundRect.png");
	m_spRoundRect->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect->setPosition(director->convertToUI(Vec2(90, 65)));
	m_pParent->addChild(m_spRoundRect);
	m_spHead = Sprite::create(headFileName);
	m_spHead->setAnchorPoint(Vec2(0,1));
	m_spHead->setPosition(director->convertToUI(pos));
	m_pParent->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 25);
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(director->convertToUI(Vec2(130,27)));
	m_pParent->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(director->convertToUI(Vec2(125, 65)));
	m_pParent->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(director->convertToUI(Vec2(180, 75)));
	m_pParent->addChild(m_lblDiamond);
	m_btnAddDiamond = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	m_btnAddDiamond->setScale9Enabled(true);
	m_btnAddDiamond->setAnchorPoint(Vec2(0, 1));
	m_btnAddDiamond->setPosition(director->convertToUI(Vec2(300,63)));
	m_pParent->addChild(m_btnAddDiamond);
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddDiamondTouch,this));
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent) :HerizelUserProfileUI(pParent)
{
	m_spRoundRect = NULL;
	m_btnAddDiamond = NULL;
}

bool UserProfileUIInMainScene::setProfile(Vec2 pos, const string headFileName, const string name, const int diamond)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	m_spRoundRect = Sprite::create("MainScene/roundRect.png");
	if (!m_spRoundRect)
	{
		return false;
	}
	m_spRoundRect->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect->setPosition(director->convertToUI(Vec2(90, 65)));
	m_pParent->addChild(m_spRoundRect);
	m_spHead = Sprite::create(headFileName);
	if (!m_spHead)
	{
		return false;
	}
	m_spHead->setAnchorPoint(Vec2(0, 1));
	m_spHead->setPosition(director->convertToUI(pos));
	m_pParent->addChild(m_spHead);
	m_lblPlayerName = LabelTTF::create(name, "Arial", 25);
	if (!m_lblPlayerName)
	{
		return false;
	}
	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
	m_lblPlayerName->setPosition(director->convertToUI(Vec2(130, 27)));
	m_pParent->addChild(m_lblPlayerName);
	m_spDianmond = Sprite::create("MainScene/diamond.png");
	if (!m_spDianmond)
	{
		return false;
	}
	m_spDianmond->setAnchorPoint(Vec2(0, 1));
	m_spDianmond->setPosition(director->convertToUI(Vec2(125, 65)));
	m_pParent->addChild(m_spDianmond);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nDiamond = diamond;
	m_lblDiamond = LabelTTF::create(buf, "Arial", 25);
	if (!m_lblDiamond)
	{
		return false;
	}
	m_lblDiamond->setColor(Color3B(224, 179, 9));
	m_lblDiamond->setAnchorPoint(Vec2(0, 1));
	m_lblDiamond->setPosition(director->convertToUI(Vec2(180, 75)));
	m_pParent->addChild(m_lblDiamond);
	m_btnAddDiamond = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	if (!m_btnAddDiamond)
	{
		return false;
	}
	m_btnAddDiamond->setScale9Enabled(true);
	m_btnAddDiamond->setAnchorPoint(Vec2(0, 1));
	m_btnAddDiamond->setPosition(director->convertToUI(Vec2(300, 63)));
	m_pParent->addChild(m_btnAddDiamond);
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddDiamondTouch, this));
	return true;
}

void UserProfileUIInMainScene::onAddDiamondTouch(Ref *pSender, Widget::TouchEventType type)
{
	log("add diamond");
}