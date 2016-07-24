#pragma once
#include "cocos2d.h"
#include "toolFunctions.h"
USING_NS_CC;

//半透明遮罩层，用于倒计时
class TimeLayer :public LayerColor
{
public:
	TimeLayer();
	virtual ~TimeLayer();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(TimeLayer);
	bool setFrameSprite(const string fileName, const Vec2& pos);

	static TimeLayer* createTimer(float time, float size, const Vec2& pos);
	void update(float delta);
	bool setTime(float time, float size, const Vec2& pos);

protected:
	Sprite* m_pFrameSprtie;							//消息框精灵

private:
	LabelTTF* timeLabel;
	float pTime;
};

