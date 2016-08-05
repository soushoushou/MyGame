#include "PopupLayer.h"

#include "ui/UIScale9Sprite.h"
#include "ui/UICheckBox.h"
#include "ui/CocosGUI.h"
#include "GamePlayScene.h"

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
#define TAG_LOGOUT_BTN	10
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
	auto roomNumPosition = ccp(layer->getPositionX(),size.height/2-5);
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
	sendBtn->setPosition(ccp(roomNumPosition.x+pEditBox_roomNum->getContentSize().width/2+20+sendBtn->getContentSize().width/2, roomNumPosition.y));
	sendBtn->setTag(TAG_SEND_BTN);
	sendBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(sendBtn, 20);
	return layer;
}

PopupLayer* PopupLayer::createRoomDialog(const char* backgroundImage, Size dialogSize) {

	layer = PopupLayer::create();

	//	layer->setSpriteBackGround(Sprite::create(backgroundImage));
	layer->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	auto size = Director::getInstance()->getWinSize();
	LabelTTF* label = LabelTTF::create("hhhhhhhh", "", 40);
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
	closeBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(closeBtn, 20);

	auto startPosition = ccp(size.width / 2, createBtn->getContentSize().height / 2 + (size.height - dialogSize.height) / 2 + 30);
	createBtn->setPosition(startPosition);
	createBtn->setTag(TAG_CREATEROOM_BTN);
	createBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(createBtn, 20);

	LabelTTF* label2 = LabelTTF::create("hhhhhhhh", "", 32);
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
	LabelTTF* label3 = LabelTTF::create("10 hhh", "", 32);
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
	LabelTTF* label4 = LabelTTF::create("10 hhh", "", 32);
	label4->setPosition(checkBox2->getContentSize().width / 2 + checkBoxPosition2.x + 20 + label4->getContentSize().width / 2, checkBoxPosition.y);
	label4->setColor(Color3B(255, 255, 255));
	layer->addChild(label4, 10);
	//getMenuButton()->addWidget(checkBox);
	if (checkBox2 != nullptr)
		layer->addChild(checkBox2, 10);
	checkBox2->setTag(TAG_CHECKBOX_20);

	LabelTTF* label5 = LabelTTF::create("hhhhhhhh", "", 32);
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
	LabelTTF* label6 = LabelTTF::create("10 hhh", "", 32);
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
	LabelTTF* label7 = LabelTTF::create("10 hhh", "", 32);
	label7->setPosition(checkBox4->getContentSize().width / 2 + checkBoxPosition4.x + 20 + label7->getContentSize().width / 2, checkBoxPosition4.y);
	label7->setColor(Color3B(255, 255, 255));
	layer->addChild(label7, 10);
	//getMenuButton()->addWidget(checkBox);
	if (checkBox4 != nullptr)
		layer->addChild(checkBox4, 10);
	checkBox4->setTag(TAG_CHECKBOX_LL);

	LabelTTF* label8 = LabelTTF::create("10 hhh", "", 20);
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
	LabelTTF* label = LabelTTF::create("hhhhhhhh", "", 40);
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
	closeBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(closeBtn, 20);
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
	commitBtn->setTag(TAG_CLOSEDIALOG_BTN);
	closeBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	commitBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	cancelBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(closeBtn, 20);
	layer->addChild(commitBtn, 20);
	layer->addChild(cancelBtn, 20);
}
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
	closeBtn->addTouchEventListener(PopupLayer::onBtnTouch);
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
	logoutBtn->addTouchEventListener(PopupLayer::onBtnTouch);
	layer->addChild(logoutBtn, 20);
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

bool PopupLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */) {

	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 2);

	// 创建图片菜单按钮
	auto item = MenuItemImage::create(
		normalImage,
		selectedImage,
		CC_CALLBACK_1(PopupLayer::buttonCallBack, this));
	item->setTag(tag);
	item->setPosition(center);

	// 添加文字说明并设置位置
	Size itemSize = item->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
	item->addChild(ttf);


	getMenuButton()->addChild(item);

	return true;
}
bool PopupLayer::addListView(/*const char* normalImage, const char* selectedImage, const char* title, int tag  = 0 */) {

	Size size = Size(200, 50);
	auto popupSize = Director::getInstance()->getWinSize();
	auto center = Point(popupSize.width / 2, popupSize.height / 2);
	auto lv = ListView::create();
	// 创建图片菜单按钮
	lv->setDirection(ui::ScrollView::Direction::VERTICAL);
	lv->setBounceEnabled(true);
	lv->setBackGroundImage("bg.jpg");//设置图片为九宫格格式。其实就和9图一个意思。只是安卓中要自己制作。这里程序会帮你生成  
	lv->setBackGroundImageScale9Enabled(true);
	lv->setContentSize(Size(200, 150));
	lv->setAnchorPoint(Point(0.5, 0.5));
	lv->setPosition(center);
	char* _image[15] = { "CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png",
		"CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png",
		"nCloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png","CloseNormal.png" };
	this->addChild(lv, 10);

	for (int i = 0; i < 15; ++i)
	{
		auto image = ImageView::create(_image[i]);

		image->setPosition(Point(image->getContentSize().width / 2, size.height / 2));

		auto bt = Button::create("joinRoom_normal.png", "joinRoom_press.png");

		bt->setScale9Enabled(true);

		bt->setContentSize(Size(size.width / 2, size.height / 2));

		bt->setPosition(Point(size.width - bt->getContentSize().width / 2, size.height / 2));

		bt->setTitleText(_image[i]);

		//itme的布局  
		auto layout = Layout::create();

		layout->setBackGroundImageScale9Enabled(true);

		layout->setBackGroundImage("bg.jpg");

		layout->setContentSize(size);

		layout->addChild(bt);
		layout->addChild(image);

		lv->addChild(layout);

	}

	lv->setItemsMargin(10);
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
bool PopupLayer::addCheckBox(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */) {

	auto size = Director::getInstance()->getWinSize();
	auto center = Point(size.width / 2, size.height / 2);

	// 创建图片菜单按钮
	CheckBox* checkBox = CheckBox::create();
	checkBox->setTouchEnabled(true);
	checkBox->loadTextures("CheckBox_UnSelect.png",
		"CheckBox_Select.png",
		"CheckBox_UnSelect.png",
		"CheckBox_UnSelect.png",
		"CheckBox_UnSelect.png");
	checkBox->setPosition(Point(center));

	checkBox->addEventListenerCheckBox(this, checkboxselectedeventselector(PopupLayer::selectedEvent));
	//getMenuButton()->addWidget(checkBox);
	if (checkBox != nullptr)
		layer->addChild(checkBox, 10);
	checkBox->setTag(0);
	//checkBox->setFocused(true);
	//m_pUiLayer->addWidget(checkBox);
	/*
	checkBox->setPosition(center);

	// 添加文字说明并设置位置
	Size itemSize = checkBox->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(Color3B(0, 0, 0));
	ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
	checkBox->addChild(ttf);*/




	return true;
}
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
			SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3");
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
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
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
	if (type == Widget::TouchEventType::ENDED)
	{
		Button* butten = (Button*)pSender;
		unsigned int tag = butten->getTag();
		switch (tag)
		{
		case TAG_CREATEROOM_BTN:
			Director::getInstance()->replaceScene(GamePlayScene::createScene());
			break;
		case TAG_CLOSEDIALOG_BTN:
			butten->getParent()->removeFromParent();
			break;
		case TAG_SEND_BTN:
			Director::getInstance()->replaceScene(GamePlayScene::createScene());
			break;
		case TAG_LOGOUT_BTN:
			butten->getParent()->removeFromParent();
			break;
		}
	}
}
void PopupLayer::buttonCallBack(Ref* pSender) {
	//Node* node = dynamic_cast<Node*>(pSender);
	////CCLog("【====PopupLayer::buttonCallBack====】touch tag: %d", node->getTag());
	//if (m_callback && m_callbackListener) {
	//	(m_callbackListener->*m_callback)(node);
	//}
	//this->removeFromParent();
	MenuItemImage* butten = (MenuItemImage*)pSender;
	unsigned int tag = butten->getTag();
	switch (tag)
	{
	case TAG_CREATEROOM_BTN:                                
		Director::getInstance()->replaceScene(GamePlayScene::createScene());
		break;
	case TAG_CLOSEDIALOG_BTN:
		this->removeFromParent();
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