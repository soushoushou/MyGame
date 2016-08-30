#include "UserProfileUI.h"
#include "PopupLayer.h"
#include "ShopLayer.h"

UserProfileUI::UserProfileUI(Node* pParent)
{
	m_strPlayerName = "";
	m_nCoin = 0;
	m_lblDiamond = NULL;
	m_spHead = NULL;
	m_lblPlayerName = NULL;
	m_pParent = pParent;
	m_spFrame = NULL;
	m_spCoin = NULL;
}


UserProfileUI::~UserProfileUI()
{
}


HerizelUserProfileUI::HerizelUserProfileUI(Node* pParent) :IUserProfileUIInGame(pParent)
{

}

//HerizelUserProfileUI::HerizelUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond
//	, const int coin) :
//IUserProfileUIInGame(pParent)
//{
//	auto director = Director::getInstance();
//	m_spFrame = Sprite::create("MainScene/userProfileFrame.png");
//	pParent->addChild(m_spFrame);
//	m_spFrame->setPosition(director->convertToUI(pos));
//	m_spHead = Sprite::create(headFileName);
//	m_spHead->setPosition(Vec2(55, 55));
//	m_spFrame->addChild(m_spHead);
//	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
//	m_lblPlayerName->setAnchorPoint(Vec2(0, 1));
//	m_lblPlayerName->setPosition(Vec2(110,90));
//	m_spFrame->addChild(m_lblPlayerName);
//	m_spCoin = Sprite::create("MainScene/coin.png");
//	m_spCoin->setAnchorPoint(Vec2(0, 1));
//	m_spCoin->setPosition(Vec2(105, 55));
//	m_spFrame->addChild(m_spCoin);
//	char buf[100];
//	sprintf(buf, "%d", diamond);
//	m_nCoin = diamond;
//	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
//	m_lblCoin->setColor(Color3B(224, 179, 9));
//	m_lblCoin->setAnchorPoint(Vec2(0, 1));
//	m_lblCoin->setPosition(Vec2(165, 45));
//	m_spFrame->addChild(m_lblCoin);
//
//	if (m_lblMultiple)
//	{
//		m_lblMultiple->release();
//	}
//	vector<string> txts = { "", "x1", "x2", "x3", "x4", "x5" };
//	m_lblMultiple = LabelTTF::create(txts[m_nMultiple], "Arial", 30);
//	m_lblMultiple->setColor(Color3B::GREEN);
//	m_lblMultiple->enableShadow(Size(3, -3), 1, 90);
//	m_lblMultiple->setAnchorPoint(Vec2(0, 1));
//	m_lblMultiple->setPosition(Vec2(15, -10));
//	m_spFrame->addChild(m_lblMultiple);
//}

void HerizelUserProfileUI::showMultiple(bool isShow /* = true */)
{
	if (m_lblMultiple);
	{
		m_lblMultiple->setVisible(isShow);
	}
}

void HerizelUserProfileUI::showBanker(bool isShow /* = true */)
{
	if (m_spBankerFrame);
	{
		m_spBankerFrame->setVisible(isShow);
	}
}

bool HerizelUserProfileUI::setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin, const int multiple)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	if (m_spFrame)
	{
		m_spFrame->removeAllChildren();
		m_spFrame->release();
	}
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
	m_spCoin = Sprite::create("MainScene/coin.png");
	if (!m_spCoin)
	{
		return false;
	}
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(Vec2(105, 55));
	m_spFrame->addChild(m_spCoin);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nCoin = diamond;
	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
	if (!m_lblCoin)
	{
		return false;
	}
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(Vec2(165, 45));
	m_spFrame->addChild(m_lblCoin);

	if (m_lblMultiple)
	{
		m_lblMultiple->release();
	}
	vector<string> txts = { "", "x1", "x2", "x3", "x4", "x5" };
	m_lblMultiple = LabelTTF::create(txts[multiple], "Arial", 30);
	if (!m_lblMultiple)
	{
		return false;
	}
	m_lblMultiple->setColor(Color3B::GREEN);
	m_lblMultiple->enableShadow(Size(3, -3), 1, 90);
	m_lblMultiple->setAnchorPoint(Vec2(0, 1));
	m_lblMultiple->setPosition(Vec2(15, -10));
	m_spFrame->addChild(m_lblMultiple);
	return true;
}

VerticalUserProfileUI::VerticalUserProfileUI(Node* pParent) :IUserProfileUIInGame(pParent)
{

}

void VerticalUserProfileUI::showMultiple(bool isShow /* = true */)
{
	if (m_lblMultiple);
	{
		m_lblMultiple->setVisible(isShow);
	}
}

void VerticalUserProfileUI::showBanker(bool isShow /* = true */)
{
	if (m_spBankerFrame)
	{
		m_spBankerFrame->setVisible(isShow);
	}
}

//VerticalUserProfileUI::VerticalUserProfileUI(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond
//	, const int coin) :
//IUserProfileUIInGame(pParent)
//{
//	auto director = Director::getInstance();
//	m_spFrame = Sprite::create("MainScene/userProfileFrameV.png");
//	pParent->addChild(m_spFrame);
//	m_spFrame->setPosition(director->convertToUI(pos));
//	m_spHead = Sprite::create(headFileName);
//	m_spHead->setPosition(Vec2(62, 120));
//	m_spFrame->addChild(m_spHead);
//	m_lblPlayerName = LabelTTF::create(name, "Arial", 20);
//	m_lblPlayerName->setPosition(Vec2(m_spFrame->getContentSize().width / 2, 60));
//	m_spFrame->addChild(m_lblPlayerName);
//	m_spCoin = Sprite::create("MainScene/coin.png");
//	m_spCoin->setAnchorPoint(Vec2(0, 1));
//	m_spCoin->setPosition(Vec2(5, 45));
//	m_spFrame->addChild(m_spCoin);
//	char buf[100];
//	sprintf(buf, "%d", diamond);
//	m_nCoin = diamond;
//	m_lblCoin = LabelTTF::create(buf, "Arial", 20);
//	m_lblCoin->setColor(Color3B(255, 252, 0));
//	m_lblCoin->setAnchorPoint(Vec2(0, 1));
//	m_lblCoin->setPosition(Vec2(55, 35));
//	m_spFrame->addChild(m_lblCoin);
//}

bool VerticalUserProfileUI::setProfileProperty(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin, const int multiple)
{
	if (!m_pParent)
	{
		return false;
	}
	auto director = Director::getInstance();
	if (m_spFrame)
	{
		m_spFrame->removeAllChildren();
		m_spFrame->release();
	}
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
	m_spCoin = Sprite::create("MainScene/coin.png");
	if (!m_spCoin)
	{
		return false;
	}
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(Vec2(5, 45));
	m_spFrame->addChild(m_spCoin);
	char buf[100];
	sprintf(buf, "%d", diamond);
	m_nCoin = diamond;
	m_lblCoin = LabelTTF::create(buf, "Arial", 20);
	if (!m_lblCoin)
	{
		return false;
	}
	m_lblCoin->setColor(Color3B(255, 252, 0));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(Vec2(55, 35));
	m_spFrame->addChild(m_lblCoin);
	return true;
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent,Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin) :
UserProfileUI(pParent)
{
	auto director = Director::getInstance();
	m_spRoundRect = Sprite::create("MainScene/roundRect.png");
	m_spRoundRect->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect->setPosition(director->convertToUI(Vec2(90, 65)));
	m_pParent->addChild(m_spRoundRect);
	m_spRoundRect2 = Sprite::create("MainScene/roundRect3.png");
	m_spRoundRect2->setAnchorPoint(Vec2(0, 1));
	m_spRoundRect2->setPosition(director->convertToUI(Vec2(380, 65)));
	m_pParent->addChild(m_spRoundRect2);
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
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));

	m_spCoin = Sprite::create("MainScene/coin.png");
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(director->convertToUI(Vec2(380, 65)));
	m_pParent->addChild(m_spCoin);
	sprintf(buf, "%d", coin);
	m_nCoin = coin;
	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(director->convertToUI(Vec2(435, 75)));
	m_pParent->addChild(m_lblCoin);
	m_btnAddCoin = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	m_btnAddCoin->setScale9Enabled(true);
	m_btnAddCoin->setAnchorPoint(Vec2(0, 1));
	m_btnAddCoin->setPosition(director->convertToUI(Vec2(540, 63)));
	m_pParent->addChild(m_btnAddCoin);
	m_btnAddCoin->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));
}

UserProfileUIInMainScene::UserProfileUIInMainScene(Node* pParent) :UserProfileUI(pParent)
{
	m_spRoundRect = NULL;
	m_btnAddDiamond = NULL;
	m_spRoundRect2 = NULL;
	m_btnAddCoin = NULL;
}

bool UserProfileUIInMainScene::setProfile(Vec2 pos, const string headFileName, const string name, const int diamond
	, const int coin)
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
	m_btnAddDiamond->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));

	m_spCoin = Sprite::create("MainScene/coin.png");
	if (!m_spCoin)
	{
		return false;
	}
	m_spCoin->setAnchorPoint(Vec2(0, 1));
	m_spCoin->setPosition(director->convertToUI(Vec2(380, 65)));
	m_pParent->addChild(m_spCoin);
	sprintf(buf, "%d", coin);
	m_nCoin = coin;
	m_lblCoin = LabelTTF::create(buf, "Arial", 25);
	if (!m_lblCoin)
	{
		return false;
	}
	m_lblCoin->setColor(Color3B(224, 179, 9));
	m_lblCoin->setAnchorPoint(Vec2(0, 1));
	m_lblCoin->setPosition(director->convertToUI(Vec2(435, 75)));
	m_pParent->addChild(m_lblCoin);
	m_btnAddCoin = Button::create("MainScene/addDiamond_normal.png", "MainScene/addDiamond_pressed.png");
	if (!m_btnAddCoin)
	{
		return false;
	}
	m_btnAddCoin->setScale9Enabled(true);
	m_btnAddCoin->setAnchorPoint(Vec2(0, 1));
	m_btnAddCoin->setPosition(director->convertToUI(Vec2(540, 63)));
	m_pParent->addChild(m_btnAddCoin);
	m_btnAddCoin->addTouchEventListener(CC_CALLBACK_2(UserProfileUIInMainScene::onAddBtnTouch, this));
	return true;
}

void UserProfileUIInMainScene::onAddBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Button* pBtn = dynamic_cast<Button*>(pSender);
	if (type == Widget::TouchEventType::ENDED)
	{
		if (pBtn == m_btnAddCoin)
		{
			//log("add coin");

			//CCScene  * scene = ShopLayer::createScene();
			//ShopLayer * layer = (ShopLayer*)(scene->getChildren()->objectAtIndex(0));
			//layer->value = "1";
			//CCDirector::sharedDirector()->replaceScene(scene);

			//Director::getInstance()->pushScene(TransitionShrinkGrow::create(0, ShopLayer::createScene()));
			Director::getInstance()->replaceScene(ShopLayer::createScene(0));
		}
		else if (pBtn == m_btnAddDiamond)
		{
			log("add diamond");
			Director::getInstance()->replaceScene(ShopLayer::createScene(1));
		}
	}

}