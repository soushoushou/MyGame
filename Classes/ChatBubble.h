#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
using namespace std;
USING_NS_CC;

class ChatBubble :public Node
{
public:
	ChatBubble(string text, string imageFile = "game/chatbuble.png", int fontsize = 20);
	virtual ~ChatBubble();
	virtual bool init();
	static ChatBubble* create(string text, string imageFile = "game/chatbuble.png", int fontsize = 20);
	void onRemove(float dt);
protected:
	ui::Scale9Sprite* m_bg;
	LabelTTF* m_context;
	string m_strMessage;
	string m_strBgFile;
	int m_nFontSize;
};

