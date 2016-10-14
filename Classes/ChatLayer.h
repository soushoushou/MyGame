#pragma once
#include "cocos2d.h"
#include "toolFunctions.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "GameSocket.h"

using namespace CocosDenshion;

using namespace cocos2d;
using namespace ui;

class ChatLayer :public LayerColor
{
public:
	ChatLayer();
	virtual ~ChatLayer();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(ChatLayer);

	//初始化聊天背景
	bool initChatBG();
	//创建快捷聊天
	bool createListView();

	void selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type);

	//初始化标题
	bool initTitle();
	//初始化按钮
	bool initButton();
	//初始化编辑框
	bool initEditBox();

	void onBtnTouch(Ref *pSender, Widget::TouchEventType type);

	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(EditBox *editBox);

	//模拟从服务器取得数据
	bool readMessage(const vector<pair<string, string>> quickMessage);

protected:
	Sprite* m_pFrameSprtie;							//œ˚œ¢øÚæ´¡È

private:
	ListView* lv;
	vector<pair<string, string>> my_quickMessage;
	CGameSocket* m_pSocket;
};

