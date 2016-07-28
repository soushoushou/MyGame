#pragma once
#include "cocos2d.h"
#include "toolFunctions.h"
USING_NS_CC;

//半透明遮罩层，用于等待连接等UI界面
class ShadeLayer :public LayerColor
{
public:
	ShadeLayer();
	virtual ~ShadeLayer();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(ShadeLayer);
	bool setFrameSprite(const string fileName, const Vec2& pos);
	bool setTitle(const string title, const string fontName, float size,const Vec2& pos);
	bool setContent(const string content, const string fontName, float size, const Vec2& pos);
	//static void onTouchEnded(Touch *touch, Event *unused_event);
protected:
	Sprite* m_pFrameSprtie;							//消息框精灵
	LabelTTF* m_plblTitle;							//消息框标题
	LabelTTF* m_plblContent;						//消息框内容
};

