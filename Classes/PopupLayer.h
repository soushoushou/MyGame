#pragma once
#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "ui/UICheckBox.h"
#include "ui/UIListView.h" 
#include "toolFunctions.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "SimpleAudioEngine.h"
#include "ui/UILayoutParameter.h"
#include "constString.h"
//USING_NS_CC_EXT;
using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;

class PopupLayer : public LayerColor,public EditBoxDelegate{
public:
	PopupLayer();
	~PopupLayer();

	virtual bool init();
	CREATE_FUNC(PopupLayer);
	static PopupLayer* createRoomDialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* joinRoomWith9Dialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* recordDialog(const char* backgroundImage, Size dialogSize);
	//static PopupLayer* wlDialog(const char* backgroundImage, Size dialogSize, const vector<pair<int, int>> quickMessage);
	static PopupLayer* wlDialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* loseDialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* settingDialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* joinRoomDialog(const char* backgroundImage, Size dialogSize);
	static PopupLayer* backDialog(const char* backgroundImage, Size dialogSize, const char* title, const char* content);
	static PopupLayer* noticeDialog(const char* backgroundImage, Size dialogSize);
	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(EditBox *editBox);
	//touch事件监听 屏蔽向下触摸
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	//virtual void registerWithTouchDispatcher();
	//标题
	void setTitle(const char* title, int fontsize = 20);
	//文本
	void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddintTop = 100);
	//设置button回调事件
	void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);
	//添加button
	bool addButton(const char* normalImage, const char* selectedImage, int tag = 0);
	//bool addListView(/*const char* normalImage, const char* selectedImage, const char* title, int tag = 0*/);
	//bool addCheckBox(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
	void selectedItemEvent(Ref *pSender, ListViewEventType type);
	virtual void onEnter();
	virtual void onExit();
	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);
	void backgroundFinish();
	bool createListView(const vector<pair<int, int>> quickMessage);
	bool createWLListView(const vector<pair<int, int>> quickMessage);
	Ref* m_callbackListener;
	SEL_CallFuncN m_callback;
	void setPlayerID(int playerID);

private:
	void buttonCallBack(Ref* pSender);
	void selectedEvent(Object* pSender, CheckBoxEventType type);
	// 文字内容两边的空白区
	int m_contentPadding;
	int m_contentPaddingTop;
	ListView* lv;
	Size m_dialogContentSize;
	EditBox* pEditBox_roomNum;
	int m_playerID;
	//set and get
	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
};