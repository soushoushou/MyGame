#pragma once
#include "cocos2d.h"
#include "toolFunctions.h"
USING_NS_CC;


enum TipType{
    Tip_gameBegin,
    Tip_hog,
    Tip_chooseMul,
    Tip_waitOther
};


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
	bool canRemove() const;
    void changeType(TipType type);
    void stopTimer();
    void setNewTime(float time);
    void setTimeAndType(float time,TipType type);
    
protected:
	Sprite* m_pFrameSprtie;							//消息框精灵

private:
	LabelTTF* timeLabel;
    Sprite* m_tipSprite;
    TipType m_type;
    CC_SYNTHESIZE(float, pTime, Time);
//	float pTime;
	bool m_bCanRemove;
};

