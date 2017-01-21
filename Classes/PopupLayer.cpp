#include "PopupLayer.h"

#include "ui/UIScale9Sprite.h"
#include "ui/UICheckBox.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"
#include "MainScene.h"

//#include "SimpleAudioEngine.h"

using namespace ui;

PopupLayer::PopupLayer() :
	m__pMenu(NULL)
	, m_contentPadding(0)
	, m_contentPaddingTop(0)
	, m_callbackListener(NULL)
	, m_callback(NULL)
	, m__sfBackGround(NULL)
	, m__s9BackGround(NULL)
	, m__ltContentText(NULL)
	, m__ltTitle(NULL)
{
}

#define TAG_CHECKBOX_10	1	
#define TAG_CHECKBOX_20	2
#define TAG_CHECKBOX_QZ		3
#define TAG_CHECKBOX_LL		4
#define TAG_CREATEROOM_BTN	5
#define TAG_CLOSEDIALOG_BTN		6
#define TAG_SEND_BTN		7
#define TAG_BACK_BTN		8
#define TAG_CHECKBOX_MUSIC	9	
#define TAG_CHECKBOX_MUSICE	10
#define TAG_LOGOUT_BTN	11
#define TAG_0_BTN 12
#define TAG_1_BTN 13
#define TAG_2_BTN 14
#define TAG_3_BTN 15
#define TAG_4_BTN 16
#define TAG_5_BTN 17
#define TAG_6_BTN 18
#define TAG_7_BTN 19
#define TAG_8_BTN 20
#define TAG_9_BTN 21
#define TAG_DEL_BTN 22
#define TAG_JOINROOM_BTN 23
#define TAG_READY_FOR_NEXT_ROUND_BTN 24
PopupLayer::~PopupLayer() {
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}
PopupLayer* layer;
bool PopupLayer::init() {
	if (!LayerColor::init()) {
		return false;
	}
	// 初始化需要的 Menu
	Menu* menu = Menu::create();
	menu->setPosition(ccp(0, 0));
	setMenuButton(menu);

	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PopupLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PopupLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PopupLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(ccc3(0, 0, 0));
	setOpacity(128);

	return true;
}

bool PopupLayer::onTouchBegan(Touch *touch, Event *event) {
	return true;
}


void PopupLayer::onTouchMoved(Touch *touch, Event *event) {

}

void PopupLayer::onTouchEnded(Touch* touch, Event* event) {

}
PopupLayer* PopupLayer::joinRoomDialog(const char* backgroundImage, Size dialogSize) {
	layer = PopupLayer::create();
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	layer->m_dialogContentSize = dialogSize;
	auto size = Director::getInstance()->getWinSize();

	
	auto pEditBox_roomNum = EditBox::create(CCSizeMake(493, 87), Scale9Sprite::create("popuplayer/EditBoxBg.png"));
	//auto size = Director::getInstance()->getWinSize();
	auto roomNumPosition = ccp((size.width)/2,size.height/2-5);
	pEditBox_roomNum->setFontColor(Color3B(0, 0, 0));
	pEditBox_roomNum->setFontSize(30);
	pEditBox_roomNum->setMaxLength(8);//设置最大长度    
	pEditBox_roomNum->setInputMode(cocos2d::ui::EditBox::InputMode::PHONE_NUMBER);
	//pEditBox_roomNum->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);
	pEditBox_roomNum->setPlaceHolder("ha ha");
	pEditBox_roomNum->setPosition(roomNumPosition);
	pEditBox_roomNum->setReturnType(EditBox::KeyboardReturnType::DONE);
	pEditBox_roomNum->setDelegate(layer);
	pEditBox_roomNum->attachWithIME();

	layer->addChild(pEditBox_roomNum,10);
	LabelTTF* label = LabelTTF::create(g_inputRoomNum, "", 36);
	label->setPosition(ccp(roomNumPosition.x - pEditBox_roomNum->getContentSize().width / 2 - 20 - label->getContentSize().width / 2, roomNumPosition.y));
	label->setColor(Color3B(255, 255, 255));
	label->setFontName("Marker Felt");
	layer->addChild(label, 10);
	Button* sendBtn = Button::create("popuplayer/sendBtn.png", "popuplayer/sendBtn_pressed.png");
	if (!sendBtn) return NULL;
	sendBtn->setScaleX(160 / sendBtn->getContentSize().width);
	sendBtn->setScaleY(80 / sendBtn->getContentSize().height);
	sendBtn->setPosition(ccp(roomNumPosition.x+pEditBox_roomNum->getContentSize().width/2+5+sendBtn->getContentSize().width/2, roomNumPosition.y));
	sendBtn->setTag(TAG_SEND_BTN);
	sendBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(sendBtn, 20);
	return layer;
}
PopupLayer* PopupLayer::joinRoomWith9Dialog(const char* backgroundImage, Size dialogSize) {
	layer = PopupLayer::create();
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	layer->m_dialogContentSize = dialogSize;
	auto size = Director::getInstance()->getWinSize();
	auto * sprite = Scale9Sprite::create("popuplayer/EditBoxBg.png");
	auto * sprite01 = Scale9Sprite::create("popuplayer/EditBox01.png");
	auto * sprite02 = Scale9Sprite::create("popuplayer/EditBox02.png");
	auto * sprite03 = Scale9Sprite::create("popuplayer/EditBox03.png");
	auto * sprite04 = Scale9Sprite::create("popuplayer/EditBox04.png");
	auto * sprite05 = Scale9Sprite::create("popuplayer/EditBox05.png");
	auto * sprite06 = Scale9Sprite::create("popuplayer/EditBox06.png");
	//上面那句话也可以根据需要这样来写：  
	//CCString* fileName = CCString::createWithFormat("Icon_%d.jpg", flag);  
	//CCSprite* sprite = CCSprite::create(fileName->getCString());  
	auto editBgPs =ccp((size.width) / 2, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	//sprite01->setPosition(editBgPs);
	//layer->addChild(sprite01,10);

	auto editBgPs01 = ccp((size.width) / 2 - 200, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite01->setPosition(editBgPs01);
	layer->addChild(sprite01, 10);

	auto editBgPs02 = ccp((size.width) / 2 - 122, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite02->setPosition(editBgPs02);
	layer->addChild(sprite02, 10);

	auto editBgPs03 = ccp((size.width) / 2 - 44, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite03->setPosition(editBgPs03);
	layer->addChild(sprite03, 10);

	auto editBgPs04 = ccp((size.width) / 2 + 34, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite04->setPosition(editBgPs04);
	layer->addChild(sprite04, 10);

	auto editBgPs05 = ccp((size.width) / 2 + 112, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite05->setPosition(editBgPs05);
	layer->addChild(sprite05, 10);

	auto editBgPs06 = ccp((size.width) / 2 + 190, (size.height + layer->m_dialogContentSize.height) / 2 - 120);
	sprite06->setPosition(editBgPs06);
	layer->addChild(sprite06, 10);

	LabelTTF* numLabel01 = LabelTTF::create("", "", 40);
	numLabel01->setPosition(editBgPs01);
	numLabel01->setName("numLabel01");
	numLabel01->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel01, 10);

	LabelTTF* numLabel02 = LabelTTF::create("", "", 40);
	numLabel02->setPosition(editBgPs02);
	numLabel02->setName("numLabel02");
	numLabel02->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel02, 10);

	LabelTTF* numLabel03 = LabelTTF::create("", "", 40);
	numLabel03->setPosition(editBgPs03);
	numLabel03->setName("numLabel03");
	numLabel03->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel03, 10);

	LabelTTF* numLabel04 = LabelTTF::create("", "", 40);
	numLabel04->setPosition(editBgPs04);
	numLabel04->setName("numLabel04");
	numLabel04->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel04, 10);

	LabelTTF* numLabel05 = LabelTTF::create("", "", 40);
	numLabel05->setPosition(editBgPs05);
	numLabel05->setName("numLabel05");
	numLabel05->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel05, 10);

	LabelTTF* numLabel06 = LabelTTF::create("", "", 40);
	numLabel06->setPosition(editBgPs06);
	numLabel06->setName("numLabel06");
	numLabel06->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel06, 10);

	/*LabelTTF* numLabel = LabelTTF::create("", "", 40);
	numLabel->setPosition(editBgPs);
	numLabel->setName("numLabel");
	numLabel->setColor(Color3B(0, 0, 0));
	layer->addChild(numLabel, 10);*/
	LabelTTF* titleLable = LabelTTF::create("please enter No", "", 40);
	titleLable->setPosition(size.width / 2, (size.height / 2 + dialogSize.height / 2 - 35));
	titleLable->setColor(Color3B(0, 0, 0));
	layer->addChild(titleLable, 10);
	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;

	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);

	Button* m0Btn = Button::create("popuplayer/0.png", "popuplayer/0_pressed.png");
	if (!m0Btn) return NULL;
	Button* m1Btn = Button::create("popuplayer/1.png", "popuplayer/1_pressed.png");
	if (!m1Btn) return NULL;
	Button* m2Btn = Button::create("popuplayer/2.png", "popuplayer/2_pressed.png");
	if (!m2Btn) return NULL;
	Button* m3Btn = Button::create("popuplayer/3.png", "popuplayer/3_pressed.png");
	if (!m3Btn) return NULL;
	Button* m4Btn = Button::create("popuplayer/4.png", "popuplayer/4_pressed.png");
	if (!m4Btn) return NULL;
	Button* m5Btn = Button::create("popuplayer/5.png", "popuplayer/5_pressed.png");
	if (!m5Btn) return NULL;
	Button* m6Btn = Button::create("popuplayer/6.png", "popuplayer/6_pressed.png");
	if (!m6Btn) return NULL;
	Button* m7Btn = Button::create("popuplayer/7.png", "popuplayer/7_pressed.png");
	if (!m7Btn) return NULL;
	Button* m8Btn = Button::create("popuplayer/8.png", "popuplayer/8_pressed.png");
	if (!m8Btn) return NULL;
	Button* m9Btn = Button::create("popuplayer/9.png", "popuplayer/9_pressed.png");
	if (!m9Btn) return NULL;
	Button* delBtn = Button::create("popuplayer/delete.png", "popuplayer/delete_pressed.png");
	if (!delBtn) return NULL;
	Button* sendBtn = Button::create("popuplayer/sendBtnJoin.png", "popuplayer/sendBtnJoin_pressed.png");
	if (!sendBtn) return NULL;

	//auto btn1Position = ccp(editBgPs.x- sprite->getContentSize().width/2+m1Btn->getContentSize().width/2-12,editBgPs.y-70);
	auto btn1Position = ccp(editBgPs.x - sprite->getContentSize().width / 2 + m1Btn->getContentSize().width / 2 - 12, editBgPs.y - 70);
	m1Btn->setPosition(btn1Position);
	m1Btn->setTag(TAG_1_BTN);
	m1Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m1Btn,10);
	auto btn2Position = ccp(editBgPs.x, btn1Position.y);
	m2Btn->setPosition(btn2Position);
	m2Btn->setTag(TAG_2_BTN);
	m2Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m2Btn, 10);
	//auto btn3Position = ccp(editBgPs.x + sprite->getContentSize().width / 2 - m1Btn->getContentSize().width / 2 + 12, btn1Position.y);
	auto btn3Position = ccp(editBgPs.x + sprite->getContentSize().width / 2 - m1Btn->getContentSize().width / 2 + 12, btn1Position.y);
	m3Btn->setPosition(btn3Position);
	m3Btn->setTag(TAG_3_BTN);
	m3Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m3Btn, 10);
	auto btn4Position = ccp(btn1Position.x, btn1Position.y - 90);
	m4Btn->setPosition(btn4Position);
	m4Btn->setTag(TAG_4_BTN);
	m4Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m4Btn, 10);
	auto btn5Position = ccp(btn2Position.x, btn1Position.y - 90);
	m5Btn->setPosition(btn5Position);
	m5Btn->setTag(TAG_5_BTN);
	m5Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m5Btn, 10);
	auto btn6Position = ccp(btn3Position.x, btn1Position.y - 90);
	m6Btn->setPosition(btn6Position);
	m6Btn->setTag(TAG_6_BTN);
	m6Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m6Btn, 10);
	auto btn7Position = ccp(btn1Position.x, btn4Position.y - 90);
	m7Btn->setPosition(btn7Position);
	m7Btn->setTag(TAG_7_BTN);
	m7Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m7Btn, 10);
	auto btn8Position = ccp(btn2Position.x, btn4Position.y - 90);
	m8Btn->setPosition(btn8Position);
	m8Btn->setTag(TAG_8_BTN);
	m8Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m8Btn, 10);
	auto btn9Position = ccp(btn3Position.x, btn4Position.y - 90);
	m9Btn->setPosition(btn9Position);
	m9Btn->setTag(TAG_9_BTN);
	m9Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m9Btn, 10);
	auto delBtnPosition = ccp(btn1Position.x, btn7Position.y - 90);
	delBtn->setPosition(delBtnPosition);
	delBtn->setTag(TAG_DEL_BTN);
	delBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(delBtn, 10);
	auto btn0Position = ccp(btn2Position.x, btn7Position.y - 90);
	m0Btn->setPosition(btn0Position);
	m0Btn->setTag(TAG_0_BTN);
	m0Btn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(m0Btn, 10);
	auto sendBtnPosition = ccp(btn3Position.x, btn7Position.y - 90);
	sendBtn->setPosition(sendBtnPosition);
	sendBtn->setTag(TAG_JOINROOM_BTN);
	sendBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(sendBtn, 10);
	return layer;
}
PopupLayer* PopupLayer::createRoomDialog(const char* backgroundImage, Size dialogSize) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	auto size = Director::getInstance()->getWinSize();
	LabelTTF* label = LabelTTF::create(g_strCreateRoom, "", 40);
	label->setPosition(size.width/2,(size.height/2+dialogSize.height/2-35));
	label->setColor(Color3B(0, 0, 0));
	layer->addChild(label,10);
	layer->m_dialogContentSize = dialogSize;
	//auto item = MenuItemImage::create(
	//	"popuplayer/close.png",
	//	"popuplayer/close_pressed.png",
	//	CC_CALLBACK_1(PopupLayer::buttonCallBack, layer));
	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;
	Button* createBtn = Button::create("popuplayer/startGame.png", "popuplayer/startGame_pressed.png");
	if (!createBtn) return NULL;
	//auto contentSize = item->getContentSize;
	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);

	auto startPosition = ccp(size.width / 2, createBtn->getContentSize().height / 2 + (size.height - dialogSize.height) / 2 + 30);
	createBtn->setPosition(startPosition);
	createBtn->setTag(TAG_CREATEROOM_BTN);
	createBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(createBtn, 20);

	LabelTTF* label2 = LabelTTF::create(g_juShuXuanZe, "", 32);
	label2->setPosition(ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3 - label2->getContentSize().width / 2 - 35, (size.height - dialogSize.height) / 2 + dialogSize.height / 3 * 2));
	label2->setColor(Color3B(255, 255, 255));
	layer->addChild(label2, 10);
	CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	checkBox->loadTextures("popuplayer/checkbox_true.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png");
	auto checkBoxPosition = ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3, (size.height - dialogSize.height) / 2 + dialogSize.height / 3 * 2);
	checkBox->setPosition(checkBoxPosition);

	checkBox->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if (checkBox != nullptr)
		layer->addChild(checkBox, 10);
	checkBox->setTag(TAG_CHECKBOX_10);
	LabelTTF* label3 = LabelTTF::create(g_tenJu, "", 32);
	label3->setPosition(checkBox->getContentSize().width/2+checkBoxPosition.x+20+label3->getContentSize().width/2,checkBoxPosition.y);
	label3->setColor(Color3B(255, 255, 255));
	layer->addChild(label3, 10);
	CheckBox* checkBox2 = CheckBox::create();
	checkBox2->setTouchEnabled(true);
	checkBox2->loadTextures("popuplayer/checkbox_true.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png");
	auto checkBoxPosition2 = ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3 * 2, (size.height - dialogSize.height) / 2 + dialogSize.height / 3 * 2);
	checkBox2->setPosition(checkBoxPosition2);
	checkBox2->setSelectedState(true);
	checkBox2->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	LabelTTF* label4 = LabelTTF::create(g_twentyJu, "", 32);
	label4->setPosition(checkBox2->getContentSize().width / 2 + checkBoxPosition2.x + 20 + label4->getContentSize().width / 2, checkBoxPosition.y);
	label4->setColor(Color3B(255, 255, 255));
	layer->addChild(label4, 10);
	//getMenuButton()->addWidget(checkBox);
	if (checkBox2 != nullptr)
		layer->addChild(checkBox2, 10);
	checkBox2->setTag(TAG_CHECKBOX_20);

	LabelTTF* label5 = LabelTTF::create(g_modeSelect, "", 32);
	label5->setPosition(ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3 - label5->getContentSize().width / 2 - 35, checkBoxPosition2.y-90));
	label5->setColor(Color3B(255, 255, 255));
	layer->addChild(label5, 10);
	
	CheckBox* checkBox3 = CheckBox::create();
	checkBox3->setTouchEnabled(true);
	checkBox3->loadTextures("popuplayer/checkbox_true.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png");
	auto checkBoxPosition3 = ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3, checkBoxPosition2.y - 90);
	checkBox3->setPosition(checkBoxPosition3);

	checkBox3->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if (checkBox3 != nullptr)
		layer->addChild(checkBox3, 10);
	checkBox3->setTag(TAG_CHECKBOX_QZ);
	LabelTTF* label6 = LabelTTF::create(g_qiangZhuangMoShi, "", 32);
	label6->setPosition(checkBox3->getContentSize().width / 2 + checkBoxPosition.x + 20 + label6->getContentSize().width / 2, checkBoxPosition3.y);
	label6->setColor(Color3B(255, 255, 255));
	layer->addChild(label6, 10);
	CheckBox* checkBox4 = CheckBox::create();
	checkBox4->setTouchEnabled(true);
	checkBox4->loadTextures("popuplayer/checkbox_true.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png",
		"popuplayer/checkbox_false.png");
	auto checkBoxPosition4 = ccp((size.width - dialogSize.width) / 2 + dialogSize.width / 3 * 2, checkBoxPosition2.y - 90);
	checkBox4->setPosition(checkBoxPosition4);
	checkBox4->setSelectedState(true);
	checkBox4->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	LabelTTF* label7 = LabelTTF::create(g_lunZhuangMoShi, "", 32);
	label7->setPosition(checkBox4->getContentSize().width / 2 + checkBoxPosition4.x + 20 + label7->getContentSize().width / 2, checkBoxPosition4.y);
	label7->setColor(Color3B(255, 255, 255));
	layer->addChild(label7, 10);
	//getMenuButton()->addWidget(checkBox);
	if (checkBox4 != nullptr)
		layer->addChild(checkBox4, 10);
	checkBox4->setTag(TAG_CHECKBOX_LL);

	LabelTTF* label8 = LabelTTF::create(g_strRoomTip, "", 20);
	label8->setPosition(createBtn->getContentSize().width / 2 + startPosition.x + 20 + label8->getContentSize().width / 2, startPosition.y);
	label8->setColor(Color3B(255, 255, 255));
	layer->addChild(label8, 10);
	return layer;
}
PopupLayer* PopupLayer::recordDialog(const char* backgroundImage, Size dialogSize) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	auto size = Director::getInstance()->getWinSize();
	LabelTTF* label = LabelTTF::create(g_strZhanJi, "", 40);
	label->setPosition(size.width / 2, (size.height / 2 + dialogSize.height / 2 - 35));
	label->setColor(Color3B(0, 0, 0));
	layer->addChild(label, 10);
	layer->m_dialogContentSize = dialogSize;
	//auto item = MenuItemImage::create(
	//	"popuplayer/close.png",
	//	"popuplayer/close_pressed.png",
	//	CC_CALLBACK_1(PopupLayer::buttonCallBack, layer));
	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;
	Button* createBtn = Button::create("popuplayer/startGame.png", "popuplayer/startGame_pressed.png");
	if (!createBtn) return NULL;
	//auto contentSize = item->getContentSize;
	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);
	return layer;}

PopupLayer* PopupLayer::wlDialog(const char* backgroundImage, Size dialogSize) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	auto size = Director::getInstance()->getWinSize();
	Size v_size = Director::getInstance()->getVisibleSize();
	LabelTTF* label = LabelTTF::create("玩家", "Arial", 20);
	label->setPosition(size.width / 2 - 80, (size.height / 2 + dialogSize.height / 2 - 235));
	
	layer->addChild(label, 10);
	LabelTTF* label2 = LabelTTF::create("积分", "Arial", 20);
	label2->setPosition(size.width / 2 +80, (size.height / 2 + dialogSize.height / 2 - 235));
	
	layer->addChild(label2, 10);
	layer->m_dialogContentSize = dialogSize;
	//auto item = MenuItemImage::create(
	//	"popuplayer/close.png",
	//	"popuplayer/close_pressed.png",
	//	CC_CALLBACK_1(PopupLayer::buttonCallBack, layer));
	Button* closeBtn = Button::create("popuplayer/commitBtn.png", "popuplayer/commitBtn_pressed.png");
	if (!closeBtn) return NULL;
	//auto contentSize = item->getContentSize;
	auto closePosition = Point((size.width - dialogSize.width)  , (size.height - dialogSize.height) / 2 + 50 );
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_READY_FOR_NEXT_ROUND_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);
	return layer;
}
bool PopupLayer::createListView(const vector<pair<int, int>> quickMessage)
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
	//lv->addEventListenerListView(this, listvieweventselector(ChatLayer::selectedItemEvent));
	
	auto button2 = Button::create("game/chat-line.png");
	button2->setPosition(Point(size.width / 2 - 220, size.height / 2 - 270));
	button2->setScale9Enabled(true);
	LabelTTF* roomNumLable = LabelTTF::create(g_strRoomID, "fonts/arial.ttf", 30);
	LabelTTF* rankLable = LabelTTF::create(g_strJiFen, "fonts/arial.ttf", 30);
	//quickLable->setPosition(Director::getInstance()->convertToUI(Vec2(quickLable->getContentSize().width / 2 + 70, quickLable->getContentSize().height / 2 + 590)));
	roomNumLable->setPosition(Point(size.width / 2 - 450, size.height / 2 - 285));
	rankLable->setPosition(Point(size.width / 2 - 230, size.height / 2 - 285));
	button2->addChild(roomNumLable);
	button2->addChild(rankLable);	
	rankLable->setColor(Color3B(255, 255, 255));
	//item的布局
	auto layout2 = Layout::create();
	layout2->setBackGroundImageScale9Enabled(true);
	layout2->setTouchEnabled(true);
	layout2->setContentSize(Size(650, 70));

	layout2->addChild(button2);
	lv->pushBackCustomItem(layout2);
	this->addChild(lv, 10);
	for (int i = 0; i < quickMessage.size(); ++i)
	{
		auto button = Button::create("game/chat-line.png");
		button->setPosition(Point(size.width / 2 - 220, size.height / 2 - 270));
		button->setScale9Enabled(true);
		//button->setName(quickMessage[i].second);
		//button->addTouchEventListener(CC_CALLBACK_2(ChatLayer::onBtnTouch, this));
		stringstream ss;
		ss << quickMessage[i].first;
		string s1 = ss.str();
		string s2;
		if (quickMessage[i].second > 0)
		{
			string s = "+";
			stringstream ss2;
			ss2 << quickMessage[i].second;
			s2 = ss2.str();
			s2 = s + s2;
		}
		else
		{
			stringstream ss2;
			ss2 << quickMessage[i].second;
			s2 = ss2.str();
		}
	

		LabelTTF* roomNumLable = LabelTTF::create(s1, "fonts/arial.ttf", 30);
		LabelTTF* rankLable = LabelTTF::create(s2, "fonts/arial.ttf", 30);
		//quickLable->setPosition(Director::getInstance()->convertToUI(Vec2(quickLable->getContentSize().width / 2 + 70, quickLable->getContentSize().height / 2 + 590)));
		roomNumLable->setPosition(Point(size.width / 2 - 450, size.height / 2 - 285));
		rankLable->setPosition(Point(size.width / 2 - 230, size.height / 2 - 285));
		button->addChild(roomNumLable);
		button->addChild(rankLable);
		if(quickMessage[i].second>0)
		{
			rankLable->setColor(Color3B(255, 255, 0));
		}
		else if(quickMessage[i].second<0)
		{
			rankLable->setColor(Color3B(0, 0, 255));
		}
		else
		{
			rankLable->setColor(Color3B(255, 255, 255));
		}
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
bool PopupLayer::createWLListView(const vector<pair<int, int>> quickMessage)
{
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	lv = ListView::create();
	lv->setDirection(ui::ScrollView::Direction::VERTICAL);	//设置为垂直方向
	lv->setBounceEnabled(true);
	lv->setTouchEnabled(true);
	//lv->setBackGroundImage("game/chat_bg.png");
	lv->setBackGroundImageScale9Enabled(true);
	lv->setContentSize(Size(700,500));
	lv->setAnchorPoint(Point(0.5, 0.5));
	lv->setPosition(Point(size.width / 2, size.height / 2-200));
	//lv->addEventListenerListView(this, listvieweventselector(ChatLayer::selectedItemEvent));
	this->addChild(lv, 10);
	for (int i = 0; i < quickMessage.size(); ++i)
	{
		auto button = Button::create("game/chat-line.png");
		button->setPosition(Point(size.width / 2 - 220, size.height / 2 - 320));
		button->setScale9Enabled(true);
		//button->setName(quickMessage[i].second);
		//button->addTouchEventListener(CC_CALLBACK_2(ChatLayer::onBtnTouch, this));
		stringstream ss;
		ss << quickMessage[i].first;
		string s1 = ss.str();
		stringstream ss2;
		ss2 << quickMessage[i].second;
		string s2 = ss2.str();
		LabelTTF* roomNumLable = LabelTTF::create(s1, "fonts/arial.ttf", 30);
		LabelTTF* rankLable = LabelTTF::create(s2, "fonts/arial.ttf", 30);
		//quickLable->setPosition(Director::getInstance()->convertToUI(Vec2(quickLable->getContentSize().width / 2 + 70, quickLable->getContentSize().height / 2 + 590)));
		roomNumLable->setPosition(Point(size.width / 2 - 450, size.height / 2 - 285));
		rankLable->setPosition(Point(size.width / 2 - 230, size.height / 2 - 285));
		button->addChild(roomNumLable);
		button->addChild(rankLable);
		if (quickMessage[i].second>0)
		{
			rankLable->setColor(Color3B(255, 255, 0));
		}
		else if (quickMessage[i].second<0)
		{
			rankLable->setColor(Color3B(0, 0, 255));
		}
		else
		{
			rankLable->setColor(Color3B(255, 255, 255));
		}
		//item的布局
		auto layout = Layout::create();
		layout->setBackGroundImageScale9Enabled(true);
		layout->setTouchEnabled(true);
		layout->setContentSize(Size(650,50));

		layout->addChild(button);
		lv->pushBackCustomItem(layout);
	}
	lv->setItemsMargin(10);

	return true;
}
PopupLayer* PopupLayer::backDialog(const char* backgroundImage, Size dialogSize,const char* title,const char* content) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	auto size = Director::getInstance()->getWinSize();
	LabelTTF* titleLable = LabelTTF::create(title, "", 40);
	titleLable->setPosition(size.width / 2, (size.height / 2 + dialogSize.height / 2 - 35));
	titleLable->setColor(Color3B(0, 0, 0));
	layer->addChild(titleLable, 10);
	LabelTTF* contentLabel = LabelTTF::create(content, "", 30);
	contentLabel->setPosition(size.width / 2, (size.height  - dialogSize.height) / 2 +dialogSize.height/3*2);
	contentLabel->setColor(Color3B(0, 0, 0));
	layer->addChild(contentLabel, 10);
	layer->m_dialogContentSize = dialogSize;
	//auto item = MenuItemImage::create(
	//	"popuplayer/close.png",
	//	"popuplayer/close_pressed.png",
	//	CC_CALLBACK_1(PopupLayer::buttonCallBack, layer));
	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;
	Button* commitBtn = Button::create("popuplayer/commitBtn.png", "popuplayer/commitBtn_pressed.png");
	if (!commitBtn) return NULL;
	Button* cancelBtn = Button::create("popuplayer/cancelBtn.png", "popuplayer/cancelBtn_pressed.png");
	if (!cancelBtn) return NULL;
	auto cancelPosition = Point((size.width + dialogSize.width) / 2  -20 - commitBtn->getContentSize().width / 2, (size.height - dialogSize.height) / 2 + 20 + commitBtn->getContentSize().height / 2);
	auto commitPosition = Point((size.width - dialogSize.width) / 2+20+commitBtn->getContentSize().width/2, (size.height - dialogSize.height) / 2 + 20 + commitBtn->getContentSize().height / 2);
	//auto contentSize = item->getContentSize;
	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	cancelBtn->setPosition(cancelPosition);
	cancelBtn->setTag(TAG_CLOSEDIALOG_BTN);
	commitBtn->setPosition(commitPosition);
	commitBtn->setTag(TAG_BACK_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	commitBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	cancelBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);
	layer->addChild(commitBtn, 20);
	layer->addChild(cancelBtn, 20);
	return layer;}
PopupLayer* PopupLayer::settingDialog(const char* backgroundImage, Size dialogSize) {
	layer = PopupLayer::create();
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	layer->m_dialogContentSize = dialogSize;
	auto size = Director::getInstance()->getWinSize();
	LabelTTF* label = LabelTTF::create("hhhhhhhh", "", 40);
	label->setPosition(size.width / 2, (size.height / 2 + dialogSize.height / 2 - 35));
	label->setColor(Color3B(0, 0, 0));
	layer->addChild(label, 10);

	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;
	Button* logoutBtn = Button::create("popuplayer/logoutBtn.png", "popuplayer/logoutBtn_pressed.png");
	if (!logoutBtn) return NULL;
	//auto contentSize = item->getContentSize;
	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);


	LabelTTF* label2 = LabelTTF::create("hhhhhhhh", "", 32);
	label2->setPosition(ccp((size.width - dialogSize.width) / 2 + label2->getContentSize().width / 2 + 65, (size.height - dialogSize.height) / 2 + dialogSize.height / 5 * 3));
	label2->setColor(Color3B(255, 255, 255));
	layer->addChild(label2, 10);
	CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	checkBox->loadTextures("popuplayer/switch_on.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png");
	auto checkBoxPosition = ccp((size.width - dialogSize.width) / 2 + label2->getContentSize().width +checkBox->getContentSize().width/2+65, (size.height - dialogSize.height) / 2 + dialogSize.height / 5 * 3);
	checkBox->setPosition(checkBoxPosition);
	
	checkBox->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if (checkBox != nullptr)
		layer->addChild(checkBox, 10);
	checkBox->setTag(TAG_CHECKBOX_MUSIC);

	LabelTTF* label3 = LabelTTF::create("hhhhhhhh", "", 32);
	label3->setPosition(ccp((size.width - dialogSize.width) / 2 + label3->getContentSize().width / 2 + 65, checkBoxPosition.y-30 - checkBox->getContentSize().height ));
	label3->setColor(Color3B(255, 255, 255));
	layer->addChild(label3, 10);
	CheckBox* checkBox2 = CheckBox::create();
	checkBox2->setTouchEnabled(true);
	checkBox2->loadTextures("popuplayer/switch_on.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png",
		"popuplayer/switch_off.png");
	auto checkBoxPosition2 = ccp((size.width - dialogSize.width) / 2 + label3->getContentSize().width + checkBox->getContentSize().width / 2 + 65, checkBoxPosition.y - 30-checkBox->getContentSize().height/2-checkBox2->getContentSize().height / 2);
	checkBox2->setPosition(checkBoxPosition2);

	checkBox2->addEventListenerCheckBox(layer, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if (checkBox2 != nullptr)
		layer->addChild(checkBox2, 10);
	checkBox2->setTag(TAG_CHECKBOX_MUSICE);
	auto director = Director::getInstance();
	auto m_spHead = Sprite::create("MainScene/timo.png");
	m_spHead->setScaleX(141.0 / m_spHead->getContentSize().width);
	m_spHead->setScaleY(138.0 / m_spHead->getContentSize().height);
	//m_spHead->setAnchorPoint(Vec2(0.5, 0.5));
	auto pos = ccp((size.width - dialogSize.width) / 2+dialogSize.width-m_spHead->getContentSize().width/2-45, checkBoxPosition.y);
	m_spHead->setPosition(pos);
	layer->addChild(m_spHead,10);


	auto logoutPosition = ccp(pos.x, pos.y-m_spHead->getContentSize().height/2-35-logoutBtn->getContentSize().height/2);
	logoutBtn->setPosition(logoutPosition);
	logoutBtn->setTag(TAG_LOGOUT_BTN);
	logoutBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(logoutBtn, 20);
	return layer;
}

PopupLayer* PopupLayer::noticeDialog(const char* backgroundImage, Size dialogSize) {
	layer = PopupLayer::create();
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	layer->m_dialogContentSize = dialogSize;
	auto size = Director::getInstance()->getWinSize();

	//公告文字
	CCDictionary* pDict = CCDictionary::createWithContentsOfFile("notice.xml");
	const char *charchinese = ((CCString*)pDict->objectForKey("name"))->getCString();
	Label* label_wenzi = Label::create(charchinese, "Arial", 25);
	label_wenzi->setHorizontalAlignment(TextHAlignment::LEFT);
	label_wenzi->setDimensions(430, 1000);
	//label_wenzi->setContentSize(Size(430,1000));
	label_wenzi->setLineBreakWithoutSpace(true);
	label_wenzi->setAnchorPoint(Point(0.5, 0.5));
	label_wenzi->setPosition(Point(size.width / 2 - 280, size.height / 2));

	//item的布局
	auto layout = Layout::create();
	layout->setBackGroundImageScale9Enabled(true);
	layout->setTouchEnabled(true);
	layout->setContentSize(Size(430, 800));
	layout->addChild(label_wenzi);

	//初始化标题
	LabelTTF* label = LabelTTF::create("gonggao", "", 40);
	label->setPosition(size.width / 2, (size.height / 2 + dialogSize.height / 2 - 35));
	label->setColor(Color3B(0, 0, 0));
	layer->addChild(label, 10);

	//滑动轮
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	ListView* lv = ListView::create();
	lv->setDirection(ui::ScrollView::Direction::VERTICAL);	//设置为垂直方向
	lv->setBounceEnabled(true);
	lv->setTouchEnabled(true);
	lv->setBackGroundImageScale9Enabled(true);
	lv->setContentSize(Size(580, 270));
	lv->setAnchorPoint(Point(0.5, 0.5));
	lv->setPosition(Point(size.width / 2, size.height / 2 - 35));
	//lv->addEventListenerListView(this, listvieweventselector(ChatLayer::selectedItemEvent));
	lv->addChild(layout);
	layer->addChild(lv,10);


	Button* closeBtn = Button::create("popuplayer/close.png", "popuplayer/close_pressed.png");
	if (!closeBtn) return NULL;
	auto closePosition = Point((size.width - dialogSize.width) / 2 + dialogSize.width, (size.height - dialogSize.height) / 2 + dialogSize.height - 35);
	closeBtn->setPosition(closePosition);
	closeBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch, layer));
	layer->addChild(closeBtn, 20);

	return layer;
}

void PopupLayer::setTitle(const char* title, int fontsize /* = 20 */) {
	LabelTTF* label = LabelTTF::create(title, "", fontsize);
	setLabelTitle(label);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop) {
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun) {
	m_callbackListener = target;
	m_callback = callfun;
}

bool PopupLayer::addButton(const char* normalImage, const char* selectedImage,  int tag /* = 0 */) {

	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 2);

	// 创建图片菜单按钮
	Button* commitBtn = Button::create("popuplayer/commitBtn.png", "popuplayer/commitBtn_pressed.png");
	if (!commitBtn) return false;
	commitBtn->setPosition(center);
	commitBtn->setTag(TAG_CREATEROOM_BTN);
	commitBtn->addTouchEventListener(CC_CALLBACK_2(PopupLayer::onBtnTouch,this));
	return true;
}

void PopupLayer::selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type)
{

	switch (type) {
	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
	{
		ListView* listView = static_cast<ListView*>(pSender);

		log("%ld", listView->getCurSelectedIndex());
	}
	break;


	case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
	{
		ListView* listView = static_cast<ListView*>(pSender);

		log("%ld", listView->getCurSelectedIndex());
	}
	break;
	default:
		break;
	}
}
//bool PopupLayer::addCheckBox(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */) {
//
//	auto size = Director::getInstance()->getWinSize();
//	auto center = Point(size.width / 2, size.height / 2);
//
//	// 创建图片菜单按钮
//	CheckBox* checkBox = CheckBox::create();
//	checkBox->setTouchEnabled(true);
//	checkBox->loadTextures("CheckBox_UnSelect.png",
//		"CheckBox_Select.png",
//		"CheckBox_UnSelect.png",
//		"CheckBox_UnSelect.png",
//		"CheckBox_UnSelect.png");
//	checkBox->setPosition(Point(center));
//
//	checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(PopupLayer::selectedEvent));
//	if (checkBox != nullptr)
//		layer->addChild(checkBox, 10);
//	checkBox->setTag(0);
//	return true;
//}
void PopupLayer::selectedEvent(Object* pSender, CheckBoxEventType type)
{
	CheckBox* checkbox = (CheckBox*)pSender;
	CheckBox* checkBox = (CheckBox*) this->getChildByTag(TAG_CHECKBOX_10);
	CheckBox* checkBox2 = (CheckBox*) this->getChildByTag(TAG_CHECKBOX_20);
	CheckBox* checkBox3 = (CheckBox*) this->getChildByTag(TAG_CHECKBOX_QZ);
	CheckBox* checkBox4 = (CheckBox*) this->getChildByTag(TAG_CHECKBOX_LL);
	unsigned int tag = checkbox->getTag();
	switch (type) {
	case cocos2d::ui::CHECKBOX_STATE_EVENT_SELECTED:
		switch (tag) {
		case TAG_CHECKBOX_10:		
			checkBox2->setSelectedState(false);
			break;
		case TAG_CHECKBOX_20:			
			checkBox->setSelectedState(false);
			break;
		case TAG_CHECKBOX_QZ:
			checkBox4->setSelectedState(false);
			break;
		case TAG_CHECKBOX_LL:
			checkBox3->setSelectedState(false);
			break;
		case TAG_CHECKBOX_MUSIC:
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			break;
		case TAG_CHECKBOX_MUSICE:
			break;
		}
		break;
	case ui::CHECKBOX_STATE_EVENT_UNSELECTED:
		switch (tag) {
		case TAG_CHECKBOX_10:
			checkBox2->setSelectedState(true);
			break;
		case TAG_CHECKBOX_20:
			checkBox->setSelectedState(true);
			break;
		case TAG_CHECKBOX_QZ:
			checkBox4->setSelectedState(true);
			break;
		case TAG_CHECKBOX_LL:
			checkBox3->setSelectedState(true);
			break;
		case TAG_CHECKBOX_MUSIC:
			SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
			break;
		case TAG_CHECKBOX_MUSICE:
			break;
		}
		break;
	default:
		break;
	}

}

void PopupLayer::onBtnTouch(Ref *pSender, Widget::TouchEventType type)
{
	Size size = Director::sharedDirector()->getWinSize();
	Button* butten = (Button*)pSender;
	string num, num01, num02, num03, num04, num05, num06;
	unsigned int tag = butten->getTag();

	if (type == Widget::TouchEventType::ENDED)
	{
		//Button* butten = (Button*)pSender;
		//string num;
		//string num,num01, num02, num03, num04, num05, num06;
		//unsigned int tag = butten->getTag();
		if (tag >= TAG_0_BTN&&tag <= TAG_JOINROOM_BTN) {
			/*LabelTTF* label = (LabelTTF *)butten->getParent()->getChildByName("numLabel");
			if (label == NULL)
			return;
			num = (string)label->getString();
			int count = num.length();
			if (tag <= TAG_9_BTN)
			{
			if (count < 6) {
			int tem = tag - TAG_0_BTN;
			stringstream ss;
			ss << tem;
			string s1 = ss.str();
			num += s1;
			label->setString(num);
			}
			else {
			return;
			}
			return;
			}
			if (tag == TAG_DEL_BTN) {
			if (count == 0) {
			return;
			}
			else {
			num=num.erase(num.length()-1);
			label->setString(num);
			return;
			}
			}*/

			LabelTTF* label01 = (LabelTTF *)butten->getParent()->getChildByName("numLabel01");
			LabelTTF* label02 = (LabelTTF *)butten->getParent()->getChildByName("numLabel02");
			LabelTTF* label03 = (LabelTTF *)butten->getParent()->getChildByName("numLabel03");
			LabelTTF* label04 = (LabelTTF *)butten->getParent()->getChildByName("numLabel04");
			LabelTTF* label05 = (LabelTTF *)butten->getParent()->getChildByName("numLabel05");
			LabelTTF* label06 = (LabelTTF *)butten->getParent()->getChildByName("numLabel06");
			if (label01 == NULL || label02 == NULL || label03 == NULL || label04 == NULL || label05 == NULL || label06 == NULL)
				return;
			num01 = (string)label01->getString();
			num02 = (string)label02->getString();
			num03 = (string)label03->getString();
			num04 = (string)label04->getString();
			num05 = (string)label05->getString();
			num06 = (string)label06->getString();

			int count01 = num01.length();
			int count02 = num02.length();
			int count03 = num03.length();
			int count04 = num04.length();
			int count05 = num05.length();
			int count06 = num06.length();

			if (tag <= TAG_9_BTN)
			{
				if (count01 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s1 = ss.str();
					num01 += s1;
					label01->setString(num01);
				}
				else if (count02 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s2 = ss.str();
					num02 += s2;
					label02->setString(num02);
				}
				else if (count03 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s3 = ss.str();
					num03 += s3;
					label03->setString(num03);
				}
				else if (count04 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s4 = ss.str();
					num04 += s4;
					label04->setString(num04);
				}
				else if (count05 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s5 = ss.str();
					num05 += s5;
					label05->setString(num05);
				}
				else if (count06 < 1) {
					int tem = tag - TAG_0_BTN;
					stringstream ss;
					ss << tem;
					string s6 = ss.str();
					num06 += s6;
					label06->setString(num06);
				}
				else {
					return;
				}
				return;
			}
			if (tag == TAG_DEL_BTN) {
				if (count06 > 0){
					num06 = num06.erase(num06.length() - 1);
					label06->setString(num06);
					return;
				}
				else if (count05 > 0){
					num05 = num05.erase(num05.length() - 1);
					label05->setString(num05);
					return;
				}
				else if (count04 > 0){
					num04 = num04.erase(num04.length() - 1);
					label04->setString(num04);
					return;
				}
				else if (count03 > 0){
					num03 = num03.erase(num03.length() - 1);
					label03->setString(num03);
					return;
				}
				else if (count02 > 0){
					num02 = num02.erase(num02.length() - 1);
					label02->setString(num02);
					return;
				}
				else if (count01 > 0){
					num01 = num01.erase(num01.length() - 1);
					label01->setString(num01);
					return;
				}
				else{
					return;
				}
			}

			if (tag == TAG_JOINROOM_BTN) {
				num = num01 + num02 + num03 + num04 + num05 + num06;
				int roomid = atoi(num.c_str());
				S_ZZ_JoinRoomReq jr(m_playerID,roomid);
				NetworkManger::getInstance()->SendRequest(jr);
			}
			return;
		}

		switch (tag)
		{
			case TAG_CREATEROOM_BTN:
			{
				S_ZZ_CreateRoomReq req(m_playerID,0,10);
				NetworkManger::getInstance()->SendRequest(req);

				break;
			}
			case TAG_CLOSEDIALOG_BTN:
				butten->getParent()->removeFromParent();
				break;
			case TAG_SEND_BTN:
				//Director::getInstance()->replaceScene(GamePlayScene::createScene(((MainScene*)this->getParent())->getPlayerID()));			
				break;
			case TAG_LOGOUT_BTN:
				butten->getParent()->removeFromParent();
				break;

			case TAG_BACK_BTN:
				if (m_callback&& m_callbackListener) {
					(m_callbackListener->*m_callback)(butten);
				}
				else {
					butten->getParent()->removeFromParent();
				}
				break;
			case TAG_READY_FOR_NEXT_ROUND_BTN:
				//发送准备消息
				S_ZZ_ReadyPlayReq req(m_playerID, 1);
				NetworkManger::getInstance()->SendRequest(req);
				//关闭积分统计显示
				butten->getParent()->removeFromParent();
				break;
		}
	}
}

void PopupLayer::setPlayerID(int playerID){
	m_playerID = playerID;
}

void PopupLayer::buttonCallBack(Ref* pSender) {
	MenuItemImage* butten = (MenuItemImage*)pSender;
	unsigned int tag = butten->getTag();
	switch (tag)
	{
	case TAG_CREATEROOM_BTN:
	{
		//S_CreateRoomReq cr;
		//NetworkManger::getInstance()->SendRequest_CreateRoom(cr);
		//Director::getInstance()->replaceScene(GamePlayScene::createScene(((MainScene*)this->getParent())->getPlayerID()));
		break;
	}
	case TAG_CLOSEDIALOG_BTN:
		this->removeFromParent();
		break;
	case TAG_BACK_BTN:
		
		break;
	}
}

void PopupLayer::onEnter() {
	LayerColor::onEnter();

	Size winSize = CCDirector::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	//	Size contentSize ;
	// 设定好参数，在运行时加载
	//如果没有设置 ContentSize ，那么采取的方案是，窗口大小与传入图片一样大
	// 	if (getContentSize().equals(this->getParent()->getContentSize())) {
	// 		getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	// 		this->addChild(getSpriteBackGround(), 0, 0);
	// 		contentSize = getSpriteBackGround()->getTexture()->getContentSize();
	// 	} else {
	// 		Scale9Sprite *background = getSprite9BackGround();
	// 		background->setContentSize(getContentSize());
	// 		background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	// 		this->addChild(background, 0, 0);
	// 		contentSize = getContentSize();
	// 	}
	//添加背景图片
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(m_dialogContentSize);
	background->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);

	// 弹出效果
	Action* popupLayer = Sequence::create(
		ScaleTo::create(0.0, 0.0),
		ScaleTo::create(0.2, 1.05),
		ScaleTo::create(0.2, 0.95),
		ScaleTo::create(0.1, 1.0),
		CallFunc::create(CC_CALLBACK_0(PopupLayer::backgroundFinish, this)),
		NULL
	);
	background->runAction(popupLayer);



}

void PopupLayer::backgroundFinish() {

	Size winSize = CCDirector::getInstance()->getWinSize();
	Point pCenter = Point(winSize.width / 2, winSize.height / 2);

	// 添加按钮，并设置其位置
	this->addChild(getMenuButton());
	float btnWidth = m_dialogContentSize.width / (getMenuButton()->getChildrenCount() + 1);

	Vector<Node*> vector = getMenuButton()->getChildren();
	Ref* pObj = NULL;
	int i = 0;
	for (Node* pObj : vector) {
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2 - m_dialogContentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - m_dialogContentSize.height / 3));
		i++;
	}

	// 显示对话框标题
	if (getLabelTitle()) {
		getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, m_dialogContentSize.height / 2 - 35.0f)));
		this->addChild(getLabelTitle());
	}

	// 显示文本内容
	if (getLabelContentText()) {
		CCLabelTTF* ltf = getLabelContentText();
		ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		ltf->setDimensions(CCSizeMake(m_dialogContentSize.width - m_contentPadding * 2, m_dialogContentSize.height - m_contentPaddingTop));
		ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
		this->addChild(ltf);
	}
}



void PopupLayer::onExit() {

	//CCLog("popup on exit.");
	CCLayerColor::onExit();
}
void PopupLayer::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void PopupLayer::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void PopupLayer::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void PopupLayer::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	switch (editBox->getTag())
	{
	case 101:
		CCLOG("EditBox_name changed");
		//m_name = text;
		break;
	case 102:
		CCLOG("EditBox_password changed");
		//m_password = text;
		break;
	default:
		break;
	}
}
