#include "PopupScene.h"
#include "PopupLayer.h"
USING_NS_CC;
CCScene* Popup::scene() {
	CCScene* scene = CCScene::create();
	CCLayer* layer = Popup::create();
	scene->addChild(layer);
	return scene;
}

bool Popup::init() {
	bool bRef = false;

	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint pointCenter = ccp(winSize.width / 2, winSize.height / 2);

		// Ìí¼Ó±³¾°Í¼Æ¬
		CCSprite* background = CCSprite::create("HelloWorld.png");
		background->setPosition(pointCenter);
		background->setScale(1.5f);
		this->addChild(background);

		//        popupLayer();

		auto loginItem = MenuItemImage::create(
			"login_button2.png", "login_button2.png", CC_CALLBACK_1(Popup::menuCallback, this));
		loginItem->setPosition(Vec2(pointCenter));

		// create menu, it's an autorelease object
		auto menu = Menu::create(loginItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 0);


		//CCLog("klt");
		bRef = true;
	} while (0);

	return bRef;
}

void Popup::popupLayer() {
	PopupLayer* pl = PopupLayer::create("popuplayer/BackGround.png", Size(400, 350));
	pl->setTitle("hhh");
	pl->setContentText("hhhh", 20, 60, 250);
	pl->setCallbackFunc(this, callfuncN_selector(Popup::buttonCallback));
	pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "submit", 1);
	pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "cancel", 0);
	pl->addCheckBox("CheckBox_UnSelect.png",
		"CheckBox_Select.png", "haha",2);
	this->addChild(pl);
}

void Popup::menuCallback(cocos2d::CCObject *pSender) {
	popupLayer();
}

void Popup::buttonCallback(cocos2d::CCNode *pNode) {
	//CCLog("button call back. tag: %d", pNode->getTag());
}