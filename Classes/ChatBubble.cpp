#include "ChatBubble.h"


ChatBubble::ChatBubble(string text, string imageFile /*= "game/chatbuble.png"*/, int fontsize /*= 20*/)
{
	m_strBgFile = imageFile;
	m_nFontSize = fontsize;
	m_strMessage = text;
}


ChatBubble::~ChatBubble()
{
}

ChatBubble* ChatBubble::create(string text, string imageFile /* = "game/chatbuble.png" */, int fontsize /* = 20 */)
{
	ChatBubble* pRet = new ChatBubble(text, imageFile, fontsize);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

void ChatBubble::onRemove(float dt)
{
	removeFromParent();
}

bool ChatBubble::init()
{
	if (!Node::init())
		return false;

	this->setAnchorPoint(Vec2(0.5,0.5));
	m_bg = ui::Scale9Sprite::create(m_strBgFile);
	m_bg->setPosition(ccp(0, 0));
	m_bg->setAnchorPoint(Vec2(0,0));
	addChild(m_bg);
	m_context = LabelTTF::create(m_strMessage, "fonts/arial.ttf", m_nFontSize);
	addChild(m_context);

	const float tmph = m_context->getContentSize().height;
	float h = m_context->getContentSize().height+20;
	float w = m_context->getContentSize().width+20;
	if (w > 160)
	{
		while (w > 160)
		{
			float avg = w / m_strMessage.length();
			int n = 160 / avg;
			m_strMessage.insert(m_strMessage.begin() + n, '\n');
			h += tmph;
			w -= n*avg;
		}
		w = 160;
		m_context->setString(m_strMessage);
	}

	m_bg->setContentSize(CCSizeMake(w, h));
	// 把显示的字符调整到控件的中间
	Size size = m_bg->getContentSize();
	m_context->setPosition(Size(size.width / 2, size.height / 2));
	return true;
}
