#include "User.h"

User::User()
{
	m_spHead = NULL;
	m_lblPlayerName = NULL;
	m_lblLevel = NULL;
}

User::User(int x, int y, const string name, const string level)
{
	m_strPlayerName = name;
	m_strLevel = level;
	m_spHead = Sprite::create("testHead.png");
	m_spHead->setPosition(Vec2(x, y));
	m_lblPlayerName = LabelTTF::create(m_strPlayerName, "Arial", 15);
	m_lblLevel = LabelTTF::create(m_strLevel, "Arial", 15);
	m_lblPlayerName->setAnchorPoint(Vec2(0, 0));
	m_lblPlayerName->setPosition(Vec2(x + 40, y + 20));
	m_lblLevel->setAnchorPoint(Vec2(0, 0));
	m_lblLevel->setPosition(Vec2(x + 40, y-10));
}

bool User::setProfile(int x, int y, const string name, const string level)
{
	m_strPlayerName = name;
	m_strLevel = level;
	m_spHead = Sprite::create("testHead.png");
	if (!m_spHead)
	{
		return false;
	}
	m_spHead->setPosition(Vec2(x, y));
	m_lblPlayerName = LabelTTF::create(m_strPlayerName, "Arial", 7);
	if (!m_lblPlayerName)
	{
		return false;
	}
	m_lblLevel = LabelTTF::create(m_strLevel, "Arial", 7);
	if (!m_lblLevel)
	{
		return false;
	}
	m_lblPlayerName->setAnchorPoint(Vec2(0, 0));
	m_lblPlayerName->setPosition(Vec2(x + 40, y + 20));
	m_lblLevel->setAnchorPoint(Vec2(0, 0));
	m_lblLevel->setPosition(Vec2(x + 40, y - 10));
	return true;
}

Sprite* User::getHeadSprite()
{
	return m_spHead;
}

LabelTTF* User::getLevel()
{
	return m_lblLevel;
}

LabelTTF* User::getPlayerName()
{
	return m_lblPlayerName;
}


User::~User()
{
}
